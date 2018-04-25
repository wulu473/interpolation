
template<typename UIt, typename WIt, typename SIt>
typename UIt::value_type
Interpolate::nonUniform1D(const SIt& sBegin, const SIt& sEnd, 
    UIt uIt, WIt wIt,
    const typename SIt::value_type& a, const typename SIt::value_type& b)
{
  typedef typename SIt::value_type S;
  typedef typename UIt::value_type U;
  typedef typename WIt::value_type W;

  SIt sIt = std::lower_bound(sBegin, sEnd,a); // points to the first not less than a
  assert(sIt != sBegin);
  sIt--;
  const SIt sSubEnd = std::lower_bound(sBegin, sEnd, b);

  auto offset = std::distance(sBegin,sIt);

  W w(0.);
  U u(0.);

  std::advance(uIt,offset);
  std::advance(wIt,offset);

  u -= (a-*sIt)*(*wIt)*(*uIt);
  w -= (a-*sIt)*(*wIt);
  for(;sIt != sSubEnd; ++sIt, ++uIt, ++wIt)
  {
    w += *wIt;
    u += (*wIt)*(*uIt);
  }
  u -= (*(sIt-1)-b)*(*(wIt-1))*(*(uIt-1));
  w -= (*(sIt-1)-b)*(*(wIt-1));

  return u/w;
}

