project('tarea3', 'cpp',
        default_options : ['cpp_std=c++20'],
        version : '0.0.2')

# Find Jack, Sndfile, Boost dependencies
jack_dep = dependency('jack')
sndfile_dep = dependency('sndfile')
boost_dep = dependency('boost', modules : ['program_options', 'system'])
benchmark_dep = dependency('benchmark', required: true)

# Common dependencies for all executables
all_deps = [jack_dep, sndfile_dep, boost_dep]

# Compiler flags for SSE 4.1, AVX2, and CPU optimization
optimization_flags = ['-msse4.1', '-mavx2', '-march=native']

# Add the optimization flags globally
add_project_arguments(optimization_flags, language: ['cpp'])

# Sources for the main application (without benchmark.cpp)
app_sources = files('main.cpp', 'jack_client.cpp', 'passthrough_client.cpp',
                    'sndfile_thread.cpp', 'waitkey.cpp', 'filter_client.cpp',
                    'biquad.cpp', 'cascade.cpp', 'parallel_simd_df2.cpp', 'parallel_simd_tdf2.cpp')

# Sources for the benchmark executable
benchmark_sources = files('benchmark.cpp', 'biquad.cpp', 'cascade.cpp', 'parallel_simd_df2.cpp', 'parallel_simd_tdf2.cpp')

# Sources for the simd_test executable
simd_test_sources = files('simd_test.cpp', 'biquad.cpp', 'cascade.cpp', 'parallel_simd_df2.cpp', 'parallel_simd_tdf2.cpp')

# Main application executable
executable('tarea3', app_sources, dependencies: all_deps)

# Benchmark executable
executable('bench', benchmark_sources, dependencies: [benchmark_dep] + all_deps)

# SIMD test executable
executable('simd_test', simd_test_sources, dependencies: all_deps)
