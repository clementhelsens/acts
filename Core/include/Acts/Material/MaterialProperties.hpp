// This file is part of the Acts project.
//
// Copyright (C) 2016-2018 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// MaterialProperties.hpp, Acts project
///////////////////////////////////////////////////////////////////

#pragma once

#include <iosfwd>
#include <vector>

#include "Acts/Material/Material.hpp"

namespace Acts {

/// Material description for an object with defined thickness.
///
/// This is intended to describe concrete surface materials.
///
/// @see Material for a description of the available parameters.
class MaterialProperties {
 public:
  /// Construct vacuum without thickness.
  MaterialProperties() = default;
  /// Construct vacuum with thickness.
  MaterialProperties(float thickness);
  /// Construct from material parameters.
  ///
  /// @param X0        is the radiation length parameter
  /// @param L0        is the nuclear interaction length
  /// @param A         is the relative atomic mass
  /// @param Z         is the atomic number
  /// @param rho       is the density
  /// @param thickness is the thickness of the material
  MaterialProperties(float X0, float L0, float A, float Z, float rho,
                     float thickness);
  /// Construct from material description.
  ///
  /// @param material  is the material description
  /// @param thickness is the thickness of the material
  MaterialProperties(const Material& material, float thickness);
  /// Construct by averaging over multiple layers.
  ///
  /// @param layers    Input layers to average over.
  /// @param normalize Whether to normalize the result to unit thickness.
  MaterialProperties(const std::vector<MaterialProperties>& layers,
                     bool normalize = true);
  ~MaterialProperties() = default;

  MaterialProperties(MaterialProperties&& mprop) = default;
  MaterialProperties(const MaterialProperties&) = default;
  MaterialProperties& operator=(MaterialProperties&&) = default;
  MaterialProperties& operator=(const MaterialProperties&) = default;

  /// Scale the material thickness.
  MaterialProperties& operator*=(float scale);

  /// Check if the material is valid, i.e. it is not vacuum.
  constexpr operator bool() const { return m_material; }

  /// Access the (average) material parameters.
  constexpr const Material& material() const { return m_material; }
  /// Return the thickness.
  constexpr float thickness() const { return m_thickness; }
  /// Return the radiation length fraction.
  constexpr float thicknessInX0() const { return m_dInX0; }
  /// Return the nuclear interaction length fraction.
  constexpr float thicknessInL0() const { return m_dInL0; }

 private:
  Material m_material;
  float m_thickness = 0.0f;
  float m_dInX0 = 0.0f;
  float m_dInL0 = 0.0f;

  friend constexpr bool operator==(const MaterialProperties& lhs,
                                   const MaterialProperties& rhs) {
    // t/X0 and t/L0 are dependent variables and need not be checked
    return (lhs.m_material == rhs.m_material) and
           (lhs.m_thickness == rhs.m_thickness);
  }
  friend constexpr bool operator!=(const MaterialProperties& lhs,
                                   const MaterialProperties& rhs) {
    return !(lhs == rhs);
  }
};

std::ostream& operator<<(std::ostream& os,
                         const MaterialProperties& materialProperties);

// Useful typedefs
using MaterialPropertiesVector = std::vector<MaterialProperties>;
using MaterialPropertiesMatrix = std::vector<MaterialPropertiesVector>;

}  // namespace Acts
