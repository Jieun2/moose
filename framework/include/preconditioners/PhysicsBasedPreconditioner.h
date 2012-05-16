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

#ifndef PHYSICSBASEDPRECONDITIONER_H
#define PHYSICSBASEDPRECONDITIONER_H

//Global includes
#include <vector>
// MOOSE includes
#include "MoosePreconditioner.h"
//libMesh includes
#include "preconditioner.h"
#include "system.h"
#include "linear_implicit_system.h"

//Forward declarations
namespace libMesh
{
  class EquationSystems;
  class MeshBase;
}


class FEProblem;
class NonlinearSystem;
class PhysicsBasedPreconditioner;

template<>
InputParameters validParams<PhysicsBasedPreconditioner>();

/**
 * Implements a segregated solve preconditioner.
 */
class PhysicsBasedPreconditioner :
    public MoosePreconditioner,
    public Preconditioner<Number>
{
public:
  /**
   *  Constructor. Initializes PhysicsBasedPreconditioner data structures
   */
  PhysicsBasedPreconditioner (const std::string & name, InputParameters params);

  /**
   * Destructor.
   */
  virtual ~PhysicsBasedPreconditioner ();

  /**
   * Add a diagonal system + possibly off-diagonals ones as well, also specifying type of preconditioning
   */
  // FIXME: use better name
  void addSystem(unsigned int var, std::vector<unsigned int> off_diag, PreconditionerType type = AMG_PRECOND);

  /**
   * Computes the preconditioned vector "y" based on input "x".
   * Usually by solving Py=x to get the action of P^-1 x.
   */
  virtual void apply(const NumericVector<Number> & x, NumericVector<Number> & y);

  /**
   * Release all memory and clear data structures.
   */
  virtual void clear ();

  /**
   * Initialize data structures if not done so already.
   */
  virtual void init ();

  /**
   * Helper function for copying values associated with variables in vectors from two different systems.
   */
  static void copyVarValues(MeshBase & mesh,
                     const unsigned int from_system, const unsigned int from_var, const NumericVector<Number> & from_vector,
                     const unsigned int to_system, const unsigned int to_var, NumericVector<Number> & to_vector);

protected:
  /// The nonlinear system this PBP is associated with (convenience reference)
  NonlinearSystem & _nl;
  /// List of linear system that build up the preconditioner
  std::vector<LinearImplicitSystem *> _systems;
  /// Holds one Preconditioner object per small system to solve.
  std::vector<Preconditioner<Number> *> _preconditioners;
  /// Holds the order the blocks are solved for.
  std::vector<unsigned int> _solve_order;
  /// Which preconditioner to use for each solve.
  std::vector<PreconditionerType> _pre_type;
  /// Holds which off diagonal blocks to compute.
  std::vector<std::vector<unsigned int> > _off_diag;

  /**
   * Holds pointers to the off-diagonal matrices.
   * This is in the same order as _off_diag.
   *
   * This is really just for convenience so we don't have
   * to keep looking this thing up through it's name.
   */
  std::vector<std::vector<SparseMatrix<Number> *> > _off_diag_mats;
};

#endif //PHYSICSBASEDPRECONDITIONER_H