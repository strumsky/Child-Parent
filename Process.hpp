 int main(int argc, char* argv[]) {
        ...
        std::vector<char*> args;
        args.push_back("ls"); //ls is just an example, process_test.cpp populates this vector from command line arguments.
        {
            Process myproc(args);  //Process object created, so child process should be created and initialized as well
        }
        //Process myproc has gone out of scope, child process should be cleaned up
        return EXIT_SUCCESS;
    }
  