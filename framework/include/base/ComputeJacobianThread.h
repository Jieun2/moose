#ifndef COMPUTEJACOBIANTHREAD_H
#define COMPUTEJACOBIANTHREAD_H

#include "ThreadedElementLoop.h"

// libMesh includes
#include "elem_range.h"

namespace Moose
{

class ComputeJacobianThread : public ThreadedElementLoop<ConstElemRange>
{
public:
  ComputeJacobianThread(Problem & problem, ImplicitSystem & sys, SparseMatrix<Number> & jacobian);

  // Splitting Constructor
  ComputeJacobianThread(ComputeJacobianThread & x, Threads::split split);
  
  virtual void preElement(const Elem *elem);
  virtual void onElement(const Elem *elem);
  virtual void onDomainChanged(short int subdomain);
  virtual void onBoundary(const Elem *elem, unsigned int side, short int bnd_id);
  virtual void postElement(const Elem * /*elem*/);
  
  void join(const ComputeJacobianThread & /*y*/);

protected:
  SparseMatrix<Number> & _jacobian;
  ImplicitSystem & _sys;
  Problem & _problem;
  std::set<Variable *> _vars;
};
  
}

#endif //COMPUTEJACOBIANTHREAD_H
