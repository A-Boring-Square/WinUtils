project('WinUtils', 'cpp', license: 'MIT', default_options: [
    'cpp_std=c++17',
])

# Define the 'fping' executable
executable('fping',
    'fast_ping/main.cpp',
    dependencies: [],
    install: true,
    install_dir: meson.current_source_dir() / 'output' / 'fping',
)

executable('fstats',
    'file_stats/main.cpp',
    dependencies: [],
    install: true,
    install_dir: meson.current_source_dir() / 'output' / 'fstats',
)
executable('timeit',
    'time_it/main.cpp',
    dependencies: [],
    install: true,
    install_dir: meson.current_source_dir() / 'output' / 'timeit',
)