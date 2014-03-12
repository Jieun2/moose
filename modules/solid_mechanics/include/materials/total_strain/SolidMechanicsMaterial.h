#ifndef SOLIDMECHANICSMATERIAL_H
#define SOLIDMECHANICSMATERIAL_H

#include "Material.h"
#include "SymmElasticityTensor.h"

//Forward Declarations
class SolidMechanicsMaterial;
class VolumetricModel;

template<>
InputParameters validParams<SolidMechanicsMaterial>();

/**
 * SolidMechanics material for use in simple applications that don't need material properties.
 */
class SolidMechanicsMaterial : public Material
{
public:
  SolidMechanicsMaterial(const std::string & name, InputParameters parameters);

protected:
  const std::string _appended_property_name;
  VariableGradient & _grad_disp_x;
  VariableGradient & _grad_disp_y;
  VariableGradient & _grad_disp_z;

  bool _has_temp;
  VariableValue & _temp;

  bool _has_c;
  VariableValue & _c;

  std::vector<VolumetricModel*> _volumetric_models;

  MaterialProperty<SymmTensor> & _stress;
  MaterialProperty<SymmElasticityTensor> & _elasticity_tensor;
  MaterialProperty<SymmElasticityTensor> & _Jacobian_mult;

  // Accumulate derivatives of strain tensors with respect to Temperature into this
  SymmTensor _d_strain_dT;

  // The derivative of the stress with respect to Temperature
  MaterialProperty<SymmTensor> & _d_stress_dT;

  MaterialProperty<SymmTensor> & _elastic_strain;


  template<typename T>
  MaterialProperty<T> & createProperty(const std::string & prop_name)
    {
      std::string name(prop_name + _appended_property_name);
      return declareProperty<T>(name);
    }

  template<typename T>
  MaterialProperty<T> & createPropertyOld(const std::string & prop_name)
    {
      std::string name(prop_name + _appended_property_name);
      return declarePropertyOld<T>(name);
    }


};

#endif //SOLIDMECHANICSMATERIAL_H