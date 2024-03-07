//#include "Filter.h"
//#include "ManagerSet.h"
//#include "CollsionManager.h"
//
//Filter::Filter(ManagerSet* _managerset)
//{
//	filters[FilterGroup::DEFAULT] = static_cast<PxU32>((UINT)FilterGroup::STATIC);
//	filters[FilterGroup::STATIC] = static_cast<PxU32>((UINT)FilterGroup::DEFAULT);
//	filters[FilterGroup::BOX] = static_cast<PxU32>((UINT)FilterGroup::DEFAULT);
//	filters[FilterGroup::SPHERE] = static_cast<PxU32>((UINT)FilterGroup::DEFAULT);
//	managerset = _managerset;
//}
//
//void Filter::SetupFiltering(PxShape* _shape, FilterGroup _filtergroup)
//{
//	PxFilterData filterData;
//	filterData.word0 = static_cast<PxU32> (_filtergroup); // word0 = own ID
//	filterData.word1 = (filters[_filtergroup]);		   // word1 = ID mask to filter pairs that trigger a
//
//	// contact callback;
//	_shape->setSimulationFilterData(filterData);
//}