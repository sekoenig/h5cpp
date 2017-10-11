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
// Created on: Sep 12, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing group creation
#include <vector>
#include "group_test_fixtures.hpp"

using boost::test_tools::output_test_stream;
using namespace hdf5;


BOOST_AUTO_TEST_SUITE(group_test)

BOOST_FIXTURE_TEST_SUITE(group_basics,BasicTestFixture)

BOOST_AUTO_TEST_CASE(test_root_group)
{
  node::Group root;
  BOOST_CHECK_NO_THROW(root = file.root());
  BOOST_CHECK(root.is_valid());
  BOOST_CHECK_EQUAL(root.type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(root.links.size(),0);
  BOOST_CHECK_EQUAL(root.nodes.size(),0);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root.link().path()),"/");
}

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  node::Group group;
  BOOST_CHECK(!group.is_valid());
}

BOOST_AUTO_TEST_CASE(test_group_creation)
{
  node::Group g = file.root();
  BOOST_CHECK_EQUAL(g.nodes.size(),0);
  BOOST_CHECK_EQUAL(g.links.size(),0);
  BOOST_CHECK_NO_THROW(g.create_group("group_1"));
  BOOST_CHECK_EQUAL(g.nodes.size(),1);
  BOOST_CHECK_EQUAL(g.links.size(),1);
  BOOST_CHECK_NO_THROW(g.create_group("group_2"));
  BOOST_CHECK_EQUAL(g.nodes.size(),2);
  BOOST_CHECK_EQUAL(g.links.size(),2);
}

BOOST_AUTO_TEST_CASE(test_group_linkview)
{
  node::Group g = file.root();
  BOOST_CHECK(!g.links.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  BOOST_CHECK(g.links.exists("group_1"));

  node::Link l;
  BOOST_CHECK_NO_THROW(l = g.links["group_1"]);
  BOOST_CHECK_EQUAL(l, g1.link());
}

BOOST_AUTO_TEST_CASE(test_group_nodeview)
{
  node::Group g = file.root();

  BOOST_CHECK_THROW(g.nodes.exists("group_1"), std::runtime_error);

  node::Group g1 = g.create_group("group_1");

  BOOST_CHECK(g.nodes.exists("group_1"));

  node::Group n;
  BOOST_CHECK_NO_THROW(n = g.nodes["group_1"]);
  BOOST_CHECK_EQUAL(n.id(), g1.id());
}

BOOST_AUTO_TEST_CASE(test_group_existence)
{
  node::Group g = file.root();

  BOOST_CHECK(!g.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  BOOST_CHECK(g.exists("group_1"));
}

BOOST_AUTO_TEST_CASE(test_group_accessor)
{
  node::Group g = file.root();
  node::Group g1 = g.create_group("group_1");

  BOOST_CHECK_EQUAL(g1.id(), g["group_1"].id());
}

BOOST_AUTO_TEST_CASE(test_funky_names)
{
  auto f = file::create("funky_names.h5",file::AccessFlags::TRUNCATE);
  node::Group g = f.root();

  BOOST_CHECK_NO_THROW(g.create_group("s p a c e y"));
  BOOST_CHECK(g.exists("s p a c e y"));

  BOOST_CHECK_NO_THROW(g.create_group(" sp"));
  BOOST_CHECK(g.exists(" sp"));

  BOOST_CHECK_NO_THROW(g.create_group("sp "));
  BOOST_CHECK(g.exists("sp "));

  BOOST_CHECK_NO_THROW(g.create_group("sp"));
  BOOST_CHECK(g.exists("sp"));

  BOOST_CHECK_NO_THROW(g.create_group(" "));
  BOOST_CHECK(g.exists(" "));

  BOOST_CHECK_NO_THROW(g.create_group("  "));
  BOOST_CHECK(g.exists("  "));

  BOOST_CHECK_NO_THROW(g.create_group("d.o.t.s"));
  BOOST_CHECK(g.exists("d.o.t.s"));

  BOOST_CHECK_NO_THROW(g.create_group(".d.o.t"));
  BOOST_CHECK(g.exists(".d.o.t"));

  BOOST_CHECK_NO_THROW(g.create_group("d..t"));
  BOOST_CHECK(g.exists("d..t"));

  BOOST_CHECK_NO_THROW(g.create_group("..dt"));
  BOOST_CHECK(g.exists("..dt"));

  BOOST_CHECK_NO_THROW(g.create_group(".."));
  BOOST_CHECK(g.exists(".."));

//  BOOST_CHECK_NO_THROW(g.create_group("g/g2"));
//  BOOST_CHECK_NO_THROW(g.create_group("./g/g3"));

  BOOST_CHECK_THROW(g.create_group("."), std::exception);
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
