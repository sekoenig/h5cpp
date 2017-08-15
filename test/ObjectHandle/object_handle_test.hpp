//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 14, 2017
//
#pragma once

#include <boost/test/unit_test.hpp>
#include <object_handle.hpp>
extern "C"{
#include<hdf5.h>
}

class TestEnvironment
{
    hdf5::ObjectHandle file_handle_;
  public:
    TestEnvironment(const std::string &filename);
    void close();

    const hdf5::ObjectHandle &file_handle() const;

};

class ObjectHandleTest
{
  private:
    hdf5::ObjectHandle::Type type_;
  public:
    ObjectHandleTest(hdf5::ObjectHandle::Type type);

    virtual ~ObjectHandleTest();

    virtual hid_t create_object() = 0;

    virtual void test_copy_construction();

    virtual void test_move_construction();

    virtual void test_copy_assignment();

    virtual void test_move_assignment();

    virtual void test_increment_reference_count();

    virtual void test_decrement_reference_count();

    hdf5::ObjectHandle::Type get_type() const;

};

std::string string_from_type(hdf5::ObjectHandle::Type type);

class FileObjectHandleTest : public ObjectHandleTest
{
  private:
    std::string filename_;
  public:
    FileObjectHandleTest(const std::string &filename);
    ~FileObjectHandleTest();

    virtual hid_t create_object();
};

class DatatypeObjectHandleTest : public ObjectHandleTest
{
  public:
    DatatypeObjectHandleTest();

    virtual hid_t create_object();
};

class DataspaceObjectHandleTest : public ObjectHandleTest
{
  public:
    DataspaceObjectHandleTest();

    virtual hid_t create_object();
};

class GroupObjectHandleTest : public ObjectHandleTest
{
  private:
    std::string filename_;
    TestEnvironment environment_;
  public:
    GroupObjectHandleTest(const std::string &filename);
    ~GroupObjectHandleTest();

    virtual hid_t create_object();
};

class DatasetObjectHandleTest : public ObjectHandleTest
{
  private:
    std::string filename_;
    TestEnvironment environment_;
    hdf5::ObjectHandle dtype_;
    hdf5::ObjectHandle dspace_;
  public:
    DatasetObjectHandleTest(const std::string &filename);
    ~DatasetObjectHandleTest();

    virtual hid_t create_object();
};

class AttributeObjectHandleTest : public ObjectHandleTest
{
  private:
    std::string filename_;
    TestEnvironment environment_;
    hdf5::ObjectHandle group_;
  public:
    AttributeObjectHandleTest(const std::string &filename);
    ~AttributeObjectHandleTest();

    virtual hid_t create_object();
};

class PropertyListObjectHandleTest : public ObjectHandleTest
{
  public:
    PropertyListObjectHandleTest();

    virtual hid_t create_object();
};

class PropertyListClassObjectHandleTest : public ObjectHandleTest
{
  public:
    PropertyListClassObjectHandleTest();

    virtual hid_t create_object();
};

class ErrorMessageObjectHandleTest : public ObjectHandleTest
{
  public:
    ErrorMessageObjectHandleTest();
    virtual hid_t create_object();
};

class ErrorStackObjectHandleTest : public ObjectHandleTest
{
  public:
    ErrorStackObjectHandleTest();
    virtual hid_t create_object();
};

class ErrorClassObjectHandleTest : public ObjectHandleTest
{
  public:
    ErrorClassObjectHandleTest();
    virtual hid_t create_object();
};




