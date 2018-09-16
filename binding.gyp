{
  "targets": [
    {
      "target_name": "tld",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "include_dirs" : ["<!@(node -p \"require('node-addon-api').include\")"],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      "libraries": [
        "-ltld", "-L<(module_root_dir)/include/libtld"
      ],
      "ldflags": [
        "-Wl,-rpath,<(module_root_dir)/include/libtld"
      ],
      "sources": [
        "main.cc",
        "src/worker/worker.cc",
        "src/worker/worker.h",
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}