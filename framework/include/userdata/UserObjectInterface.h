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

#ifndef USEROBJECTINTERFACE_H
#define USEROBJECTINTERFACE_H

#include "InputParameters.h"
#include "ParallelUniqueId.h"

class Problem;
class UserObject;

/**
 * Interface for objects that need to use user objects
 */
class UserObjectInterface
{
public:
  /**
   * @param params The parameters used by the object being instantiated. This
   *        class needs them so it can get the user object named in the input file,
   *        but the object calling getUserObject only needs to use the name on the
   *        left hand side of the statement "user_object = user_object_name"
   */
  UserObjectInterface(InputParameters & params);

  /**
   * Get an user object with a given name
   * @param name The name of the parameter key of the user object to retrieve
   * @return The user object with name associated with the parameter 'name'
   */
  const UserObject & getUserObject(const std::string & name);

  /**
   * Get a user object with a given name
   * @param name The name of the user object to retrieve
   * @return The user object with name 'name'
   */
  const UserObject & getUserObjectByName(const std::string & name);

private:
  Problem & _udi_problem;
  /// Thread ID
  THREAD_ID _udi_tid;
  /// Parameters of the object with this interface
  InputParameters _udi_params;
};

#endif //USEROBJECTFACE_H