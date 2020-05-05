#include <libjson/pointer.hxx>

#include <libunittest/unittest.hxx>

#include <string>

DEFINE_TEST("simple object")
{
  std::string json = R"JSON(
    { "haystack": "needle" }
  )JSON";

  auto variant = json::resolve(json, "/haystack");

  TEST_TRUE(variant.is_string());
  TEST_EQUAL(variant.get< std::string >(), "needle");
}

DEFINE_TEST("simple array")
{
  std::string json = R"JSON(
    [ "needle" ]
  )JSON";

  auto variant = json::resolve(json, "/0");

  TEST_TRUE(variant.is_string());
  TEST_EQUAL(variant.get< std::string >(), "needle");
}

DEFINE_TEST("complex")
{
  std::string json = R"JSON(
    {
      "employees": [
        {
          "name": "Doe, John",
          "departments": ["HQ"],
          "age": 37
        },
        {
          "name": "Doe, Jane",
          "departments": ["Software", "Finance"],
          "age": 29
        }
      ]
    }
  )JSON";

  auto emp_0_name = json::resolve(json, "/employees/0/name");
  auto emp_0_department_0 = json::resolve(json, "/employees/0/departments/0");
  auto emp_0_age = json::resolve(json, "/employees/0/age");

  auto emp_1_name = json::resolve(json, "/employees/1/name");
  auto emp_1_department_0 = json::resolve(json, "/employees/1/departments/0");
  auto emp_1_department_1 = json::resolve(json, "/employees/1/departments/1");
  auto emp_1_age = json::resolve(json, "/employees/1/age");

  TEST_TRUE(emp_0_name.is_string());
  TEST_TRUE(emp_0_department_0.is_string());
  TEST_TRUE(emp_0_age.is_number());
  TEST_TRUE(emp_0_age.is_unsigned());

  TEST_TRUE(emp_1_name.is_string());
  TEST_TRUE(emp_1_department_0.is_string());
  TEST_TRUE(emp_1_department_1.is_string());
  TEST_TRUE(emp_1_age.is_number());
  TEST_TRUE(emp_1_age.is_unsigned());

  TEST_EQUAL(emp_0_name.get< std::string >(), "Doe, John");
  TEST_EQUAL(emp_0_department_0.get< std::string >(), "HQ");
  TEST_EQUAL(emp_0_age.get< signed >(), 37);
  TEST_EQUAL(emp_0_age.get< unsigned >(), 37);

  TEST_EQUAL(emp_1_name.get< std::string >(), "Doe, Jane");
  TEST_EQUAL(emp_1_department_0.get< std::string >(), "Software");
  TEST_EQUAL(emp_1_department_1.get< std::string >(), "Finance");
  TEST_EQUAL(emp_1_age.get< signed >(), 29);
  TEST_EQUAL(emp_1_age.get< unsigned >(), 29);
}
