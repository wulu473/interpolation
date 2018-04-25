
#ifndef INTERPOLATE_H_
#define INTERPOLATE_H_


namespace Interpolate
{
  template<typename UIt, typename WIt, typename SIt>
  typename UIt::value_type nonUniform1D(const SIt&, const SIt&, UIt, WIt,
                                        const typename SIt::value_type&,
                                        const typename SIt::value_type&);
}

#include "InterpolateTemplates.cpp"
#endif
