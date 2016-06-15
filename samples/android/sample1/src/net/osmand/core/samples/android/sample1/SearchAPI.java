package net.osmand.core.samples.android.sample1;

import android.os.AsyncTask;

import net.osmand.core.jni.AmenitiesByNameSearch;
import net.osmand.core.jni.Amenity;
import net.osmand.core.jni.Amenity.DecodedCategory;
import net.osmand.core.jni.AreaI;
import net.osmand.core.jni.DecodedCategoryList;
import net.osmand.core.jni.IObfsCollection;
import net.osmand.core.jni.IQueryController;
import net.osmand.core.jni.ISearch;
import net.osmand.core.jni.LatLon;
import net.osmand.core.jni.ObfInfo;
import net.osmand.core.jni.ObfsCollection;
import net.osmand.core.jni.QStringStringHash;
import net.osmand.core.jni.Utilities;

import java.util.ArrayList;
import java.util.List;

public class SearchAPI {

	private ObfsCollection obfsCollection;
	private AreaI searchableArea;
	private SearchRequestExecutor executor;

	interface SearchAPICallback {
		void onSearchFinished(List<SearchItem> searchItems, boolean cancelled);
	}

	public SearchAPI(ObfsCollection obfsCollection) {
		this.obfsCollection = obfsCollection;
		executor = new SearchRequestExecutor();
	}

	public AreaI getSearchableArea() {
		return searchableArea;
	}

	public void setSearchableArea(AreaI searchableArea) {
		this.searchableArea = searchableArea;
	}

	public void startSearch(String keyword, int maxSearchResults, SearchAPICallback apiCallback) {
		executor.run(new SearchRequest(keyword, maxSearchResults, apiCallback), true);
	}

	public void cancelSearch() {
		executor.cancel();
	}


	public class SearchRequestExecutor {

		private SearchRequest ongoingSearchRequest;
		private SearchRequest nextSearchRequest;

		public void run(SearchRequest searchRequest, boolean cancelCurrentRequest) {
			if (ongoingSearchRequest != null) {
				nextSearchRequest = searchRequest;
				if (cancelCurrentRequest) {
					ongoingSearchRequest.cancel();
				}
			} else {
				ongoingSearchRequest = searchRequest;
				nextSearchRequest = null;
				searchRequest.setOnFinishedCallback(new Runnable() {
					@Override
					public void run() {
						operationFinished();
					}
				});
				searchRequest.run();
			}
		}

		public void cancel() {
			if (nextSearchRequest != null) {
				nextSearchRequest = null;
			}
			if (ongoingSearchRequest != null) {
				ongoingSearchRequest.cancel();
			}
		}

		private void operationFinished() {
			ongoingSearchRequest = null;
			if (nextSearchRequest != null) {
				run(nextSearchRequest, false);
			}
		}
	}

	public class SearchRequest {
		private String keyword;
		private int maxSearchResults;
		private Runnable onFinished;
		private SearchAPICallback apiCallback;

		private boolean cancelled;
		private int resCount;

		public SearchRequest(String keyword, int maxSearchResults, SearchAPICallback apiCallback) {
			this.keyword = keyword;
			this.maxSearchResults = maxSearchResults;
			this.apiCallback = apiCallback;
		}

		public void run() {

			new AsyncTask<String, Void, List<SearchItem>>() {
				@Override
				protected List<SearchItem> doInBackground(String... params) {
					return doSearch(params[0]);
				}

				@Override
				protected void onPostExecute(List<SearchItem> searchItems) {

					if (onFinished != null) {
						onFinished.run();
					}

					if (apiCallback != null) {
						apiCallback.onSearchFinished(searchItems, cancelled);
					}
				}
			}.execute(keyword);
		}

		private List<SearchItem> doSearch(String keyword) {
			System.out.println("=== Start search");
			resCount = 0;

			final List<SearchItem> searchItems = new ArrayList<>();

			AmenitiesByNameSearch byNameSearch = new AmenitiesByNameSearch(obfsCollection);
			AmenitiesByNameSearch.Criteria criteria = new AmenitiesByNameSearch.Criteria();
			criteria.setName(keyword);

			IObfsCollection.IAcceptorFunction acceptorFunction = new IObfsCollection.IAcceptorFunction() {
				@Override
				public boolean method(ObfInfo obfInfo) {

					boolean res = true;//obfInfo.containsPOIFor(searchableArea);
					return res && resCount < maxSearchResults && !cancelled;
				}
			};

			criteria.setSourceFilter(acceptorFunction.getBinding());

			ISearch.INewResultEntryCallback newResultEntryCallback = new ISearch.INewResultEntryCallback() {
				@Override
				public void method(ISearch.Criteria criteria, ISearch.IResultEntry resultEntry) {
					Amenity amenity = new ResultEntry(resultEntry).getAmenity();
					searchItems.add(new AmenitySearchItem(amenity));
					System.out.println("Poi found === " + amenity.getNativeName());
					resCount++;
				/*
				QStringStringHash locNames = amenity.getLocalizedNames();
				if (locNames.size() > 0) {
					QStringList keys = locNames.keys();
					StringBuilder sb = new StringBuilder("=== Localized names: ");
					for (int i = 0; i < keys.size(); i++) {
						String key = keys.get(i);
						sb.append(key).append("=").append(locNames.get(key)).append(" | ");
					}
					System.out.println(sb.toString());
				}
				*/
				}
			};

			byNameSearch.performSearch(criteria, newResultEntryCallback.getBinding(), new IQueryController() {
				@Override
				public boolean isAborted() {
					return resCount >= maxSearchResults || cancelled;
				}
			});

			System.out.println("=== Finish search");

			return searchItems;
		}

		public void cancel() {
			cancelled = true;
		}

		public void setOnFinishedCallback(Runnable onFinished) {
			this.onFinished = onFinished;
		}
	}

	private static class ResultEntry extends AmenitiesByNameSearch.ResultEntry {
		protected ResultEntry(ISearch.IResultEntry resultEntry) {
			super(ISearch.IResultEntry.getCPtr(resultEntry), false);
		}
	}

	public static abstract class SearchItem {

		public SearchItem() {
		}

		public abstract String getNativeName();

		public abstract String getLocalizedName();

		public abstract String getTypeName();

		public abstract String getSubTypeName();

		public abstract double getLatitude();

		public abstract double getLongitude();

		@Override
		public String toString() {
			return getNativeName() + " {lat:" + getLatitude() + " lon: " + getLongitude() + "}";
		}
	}

	public static class AmenitySearchItem extends SearchItem {

		private String nativeName;
		private String localizedName;
		private String category;
		private String subcategory;
		private double latitude;
		private double longitude;

		public AmenitySearchItem(Amenity amenity) {
			nativeName = amenity.getNativeName();
			QStringStringHash locNames = amenity.getLocalizedNames();
			if (locNames.has_key(MapUtils.LANGUAGE)) {
				localizedName = locNames.get(MapUtils.LANGUAGE);
			}
			/*
			if (locNames.size() > 0) {
				QStringList keys = locNames.keys();
				for (int i = 0; i < keys.size(); i++) {
					String key = keys.get(i);
					localizedNamesMap.put(key, locNames.get(key));
				}
			}
			*/

			DecodedCategoryList catList = amenity.getDecodedCategories();
			if (catList.size() > 0) {
				DecodedCategory decodedCategory = catList.get(0);
				category = decodedCategory.getCategory();
				subcategory = decodedCategory.getSubcategory();
			}

			LatLon latLon = Utilities.convert31ToLatLon(amenity.getPosition31());
			latitude = latLon.getLatitude();
			longitude = latLon.getLongitude();
		}

		@Override
		public String getNativeName() {
			return nativeName;
		}

		@Override
		public String getLocalizedName() {
			return localizedName != null ? localizedName : nativeName;
		}

		@Override
		public String getTypeName() {
			return category;
		}

		@Override
		public String getSubTypeName() {
			return subcategory;
		}

		@Override
		public double getLatitude() {
			return latitude;
		}

		@Override
		public double getLongitude() {
			return longitude;
		}
	}
}
