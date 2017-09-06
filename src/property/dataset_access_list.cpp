//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 22, 2017
//

#include <h5cpp/property/dataset_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace hdf5 {
namespace property {

ChunkCacheParameters::ChunkCacheParameters() noexcept:
    nslots_(0),
    nbytes_(0),
    w0_(0.0)
{}

ChunkCacheParameters::ChunkCacheParameters(size_t nslots,size_t nbytes,double preempt_policy) noexcept:
    nslots_(nslots),
    nbytes_(nbytes),
    w0_(preempt_policy)
{}

void ChunkCacheParameters::chunk_slots(size_t nslots) noexcept
{
  nslots_ = nslots;
}

size_t ChunkCacheParameters::chunk_slots() const noexcept
{
  return nslots_;
}

void ChunkCacheParameters::chunk_cache_size(size_t size) noexcept
{
  nbytes_ = size;
}

size_t ChunkCacheParameters::chunk_cache_size() const noexcept
{
  return nbytes_;
}

void ChunkCacheParameters::preemption_policy(double value) noexcept
{
  w0_ = value;
}
double ChunkCacheParameters::preemption_policy() const noexcept
{
  return w0_;
}

DatasetAccessList::DatasetAccessList():
    LinkAccessList(kDatasetAccess)
{}

DatasetAccessList::~DatasetAccessList()
{}

void DatasetAccessList::chunk_cache_parameters(const ChunkCacheParameters &params) const
{
  if(H5Pset_chunk_cache(static_cast<hid_t>(*this),params.chunk_slots(),
                        params.chunk_cache_size(),params.preemption_policy())<0)
  {
    std::runtime_error("Failure setting chunk cache parameters!");
  }

}

ChunkCacheParameters DatasetAccessList::chunk_cache_parameters() const
{
  size_t nslots = 0;
  size_t nbytes = 0;
  double w0 = 0.0;
  if(H5Pget_chunk_cache(static_cast<hid_t>(*this),&nslots,&nbytes,&w0)<0)
  {
    std::runtime_error("Failure retrieving chunk cache parameters!");
  }
  return ChunkCacheParameters(nslots,nbytes,w0);
}


}
}