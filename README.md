# cli_usage
A simple module for creating a usage guide. This module is inspired by [command-line-usage](https://github.com/75lb/command-line-usage).

## Getting Started
To see an example, just call the first rule of the Makefile:
```
$ make
```

Then you can see the guide by firing the program:
```
$ ./example
```

## Synopsis
A usage guide is created by first defining several sections, e.g. a description section, synopsis, option list, examples, footer etc. Each section has an optional header and some content.
```
size = 3;
sections = NULL;
option_defs = init_option_defs(size);
option_defs[0] = add_def("help", "h", OPT_NULL);
option_defs[0].description = "Display this usage guide.";
option_defs[1] = add_def("src", NULL, OPT_STRING);
option_defs[1].multiple = 1;
option_defs[1].description = "The input files to process.";
option_defs[1].label = "file ...";
option_defs[2] = add_def("timeout", "t", OPT_INTEGER);
option_defs[2].description = "Timeout value in ms.";
option_defs[2].label = "ms";
options_list = init_options_list(option_defs, size);
add_section(&sections, "A typical app", "Generates something important.", NULL);
add_section(&sections, "Options", NULL, options_list);
```

This section data is passed to command_line_usage() which renders the usage guide.
```
command_line_usage(sections);
```

![usage](https://github.com/wbeuil/cli_usage/raw/master/example.png)

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details