// This file is part of the Acts project.
//
// Copyright (C) 2016-2018 Acts project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// BinnedSurfaceMaterial.h, Acts project
///////////////////////////////////////////////////////////////////

#pragma once
#include "Acts/Material/MaterialProperties.hpp"
#include "Acts/Material/SurfaceMaterial.hpp"
#include "Acts/Utilities/BinUtility.hpp"
#include "Acts/Utilities/Definitions.hpp"

namespace Acts {

/// @class BinnedSurfaceMaterial
///
/// It extends the SurfaceMaterial base class and is an array pf
/// MaterialProperties. This is not memory optimised as every bin
/// holds one material property object.

class BinnedSurfaceMaterial : public SurfaceMaterial
{
public:
  /// Default Constructor - deleted
  BinnedSurfaceMaterial() = delete;

  /// Explizit constructor with only full MaterialProperties,
  /// for one-dimensional binning.
  ///
  /// The split factors:
  ///    - 1. : oppositePre
  ///    - 0. : alongPre
  ///  ===> 1 Dimensional array
  ///
  /// @param binUtility defines the binning structure on the surface
  /// @param fullProperties is the vector of properties as recorded
  /// @param splitFactor is the pre/post splitting directive
  /// @param entries is the (optional) number of mapping entries
  BinnedSurfaceMaterial(const BinUtility&               binUtility,
                        const MaterialPropertiesVector& fullProperties,
                        double                          splitFactor = 0.,
                        size_t                          entries     = 1);

  /// Explizit constructor with only full MaterialProperties,
  /// for two-dimensional binning.
  ///
  /// The split factors:
  ///    - 1. : oppositePre
  ///    - 0. : alongPre
  ///  ===> 1 Dimensional array
  ///
  /// @param binUtility defines the binning structure on the surface
  /// @param fullProperties is the vector of properties as recorded
  /// @param splitFactor is the pre/post splitting directive
  /// @param entries is the (optional) number of mapping entries
  BinnedSurfaceMaterial(const BinUtility&               binutility,
                        const MaterialPropertiesMatrix& fullProperties,
                        double                          splitFactor = 0.,
                        size_t                          entries     = 1);

  /// Copy Constructor
  ///
  /// @param bsm is the source object to be copied
  BinnedSurfaceMaterial(const BinnedSurfaceMaterial& bsm);

  /// Destructor
  virtual ~BinnedSurfaceMaterial();

  /// Pseudo-Constructor clone()
  BinnedSurfaceMaterial*
  clone() const final override;

  /// Assignment operator
  BinnedSurfaceMaterial&
  operator=(const BinnedSurfaceMaterial& lmp);

  /// Scale operator
  ///
  /// @param scale is the scale factor for the full material
  BinnedSurfaceMaterial&
  operator*=(double scale) final override;

  /// Return the BinUtility
  const BinUtility&
  binUtility() const;

  /// @copydoc SurfaceMaterial::fullMaterial
  const MaterialPropertiesMatrix&
  fullMaterial() const;

  /// @copydoc SurfaceMaterial::material(const Vector2D&)
  const MaterialProperties*
  material(const Vector2D& lp) const final override;

  /// @copydoc SurfaceMaterial::material(const Vector3D&)
  const MaterialProperties*
  material(const Vector3D& gp) const final override;

  /// @copydoc SurfaceMaterial::material(size_t, size_t)
  const MaterialProperties*
  material(size_t bin0, size_t bin1) const final override;

  /// access to the entries
  /// this is needed for averageing mapps
  size_t
  entries() const;

  /// Output Method for std::ostream, to be overloaded by child classes
  std::ostream&
  dump(std::ostream& sl) const final override;

private:
  /// The helper for the bin finding
  BinUtility m_binUtility;

  /// The five different MaterialProperties
  MaterialPropertiesMatrix m_fullMaterial;

  /// The number of entries used
  size_t m_entries;

  /// helper method - to clear the material
  void
  clearMaterial();

  /// helper method - to refill the material
  void
  fillMaterial(const MaterialPropertiesMatrix& matMatrix);
};

inline const BinUtility&
BinnedSurfaceMaterial::binUtility() const
{
  return (m_binUtility);
}

inline const MaterialPropertiesMatrix&
BinnedSurfaceMaterial::fullMaterial() const
{
  return m_fullMaterial;
}

inline const MaterialProperties*
BinnedSurfaceMaterial::material(size_t bin0, size_t bin1) const
{
  return m_fullMaterial[bin1][bin0];
}

inline size_t
BinnedSurfaceMaterial::entries() const
{
  return m_entries;
}
}