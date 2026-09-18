#include <pans/macros.h>
#include <iostream>
#include <limits>
#include <type_traits>
#include <cassert>

static_assert(sizeof(u8) == 1 && std::is_unsigned_v<u8>);

void test_type_and_constants()
{
    // ASSERT_NOEFFECT(sizeof(u8) == 1 && std::is_unsigned_v<u8>);
}

[[nodiscard]] int test_assert_retval()
{
    PANS_RETVAL(false, -1, 0);
    return 0;
}

int main()
{
#ifdef PANS_DEBUG
    std::cout << "This program is compiled in debug mode. Assert will terminate the program on failure" << std::endl;
#endif

#ifdef NDEBUG
    std::cout << "This program is compiled in debug mode. Assert will do nothing on failure" << std::endl;
#endif

    auto retval1 = test_assert_retval();
    std::cout << "test_assert_retval() returned: " << retval1 << std::endl;
    std::cout << "hello!" << std::endl;
}