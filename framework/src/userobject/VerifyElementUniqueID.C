/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "VerifyElementUniqueID.h"
#include "SubProblem.h"

#include <algorithm>

template<>
InputParameters validParams<VerifyElementUniqueID>()
{
  InputParameters params = validParams<ElementUserObject>();
  return params;
}

VerifyElementUniqueID::VerifyElementUniqueID(const std::string & name, InputParameters parameters) :
    ElementUserObject(name, parameters)
{}

// This object can't test every possible scenario.  For instance, it can't detect recycled ids
// It's only designed to make sure that all ids are unique in any given
void
VerifyElementUniqueID::initialize()
{
  _all_ids.clear();
  _all_ids.reserve(_subproblem.mesh().getMesh().n_local_nodes());
}

void
VerifyElementUniqueID::execute()
{
#ifdef LIBMESH_ENABLE_UNIQUE_ID
  _all_ids.push_back(_current_elem->unique_id());
#else
  _all_ids.push_back(0);
#endif
}

void
VerifyElementUniqueID::threadJoin(const UserObject &y)
{
  const VerifyElementUniqueID & uo = static_cast<const VerifyElementUniqueID &>(y);

  _all_ids.insert(_all_ids.end(), uo._all_ids.begin(), uo._all_ids.end());
}

void
VerifyElementUniqueID::finalize()
{
  // On Parallel Mesh we have to look at all the ids over all the processors
  if (_subproblem.mesh().isParallelMesh())
    Parallel::allgather(_all_ids);

  std::sort(_all_ids.begin(), _all_ids.end());
  std::vector<dof_id_type>::iterator it_end = std::unique(_all_ids.begin(), _all_ids.end());
  if (it_end != _all_ids.end())
    mooseError("Duplicate unique_ids found!");
}
