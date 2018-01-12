//   Copyright (c) 2017 Shahrzad Shirzad
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/phylanx.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <utility>
#include <vector>

void test_identity()
{
    phylanx::execution_tree::primitive val =
        hpx::new_<phylanx::execution_tree::primitives::variable>(
            hpx::find_here(), phylanx::ir::node_data<double>(5.0));

    phylanx::execution_tree::primitive identity =
        hpx::new_<phylanx::execution_tree::primitives::identity>(
            hpx::find_here(),
            std::vector<phylanx::execution_tree::primitive_argument_type>{
                std::move(val)});

    hpx::future<phylanx::execution_tree::primitive_result_type> f =
        identity.eval();

    auto result = phylanx::execution_tree::extract_numeric_value(f.get());
    HPX_TEST_EQ(
        phylanx::ir::node_data<double>(blaze::IdentityMatrix<double>(5UL)),
        result);
}

int main(int argc, char* argv[])
{
    test_identity();
    return hpx::util::report_errors();
}
