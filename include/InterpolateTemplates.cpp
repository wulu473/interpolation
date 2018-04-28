#include <iostream>

template<typename UIt, typename WIt, typename SIt>
typename UIt::value_type
Interpolate::nonUniform1D(const SIt& sItConst, SIt sEnd, 
    UIt uIt, WIt wIt,
    const typename SIt::value_type& a, const typename SIt::value_type& b)
{
  SIt sIt = sItConst;
  return nonUniform1D(sIt,sEnd,uIt,wIt,a,b);
}

//! Compute the weighted average on a non-uniformly spaced grid
/**
 * \warning The coordinates are face centred whereas the states and weights are cell centred. 
 * Therefore s.end - s.begin - 1 == u.end - u.begin
 *
 * \note that this routine changes the passed position of the sIt iterator. 
 * This allows to optimisation if the beginning of the sub array is known. In which case the iterator should point to the right face of the first cell.
 *
 * \warning Assumption of *sIt < a and b < *sEnd
 *
 * \param[in,out] sIt Iterator pointing to the beginning of an array holding face coordinates of the left face. After this routine the iterator will point to the right face of the last cell that was used
 * \param[in] sEnd Iterator pointing to the end of the same array
 * \param[in] uIt Iterator pointing to the data array of cell centred states
 * \param[in] wIt Iterator pointing to the weights array
 * \param[in] a Coordinate of left bound of the average
 * \param[in] b Coordinate of the right bound of the average
 *
 */
template<typename UIt, typename WIt, typename SIt>
typename UIt::value_type
Interpolate::nonUniform1D(SIt& sIt, SIt sEnd, 
    UIt uIt, WIt wIt,
    const typename SIt::value_type& a, const typename SIt::value_type& b)
{
  typedef typename SIt::value_type S;
  typedef typename UIt::value_type U;
  typedef typename WIt::value_type W;

  const SIt sBegin = sIt;
  sIt = std::lower_bound(sBegin, sEnd,a); // points to the first not less than a
  sIt--;

  const SIt sSubEnd = std::lower_bound(sBegin, sEnd, b);
  assert(sSubEnd != sEnd);

  const auto offset = std::distance(sBegin,sIt);
  std::advance(uIt,offset);
  std::advance(wIt,offset);

  W w(0.);
  U u(0.);

  u -= (a-*sIt)*(*wIt)*(*uIt);
  w -= (a-*sIt)*(*wIt);
  for(;sIt != sSubEnd; ++sIt, ++uIt, ++wIt)
  {
    w += *wIt;
    u += (*wIt)*(*uIt);
  }
  u -= (*(sIt)-b)*(*(wIt-1))*(*(uIt-1));
  w -= (*(sIt)-b)*(*(wIt-1));

  return u/w;
}

