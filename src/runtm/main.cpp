#include <turmac.h>
#include <iostream>

/*-------- CONSTANTS, VARIABLES & DECLARATIONS --------*/
static const std::string USAGE = "usage: runtm <tm-file> <input-file> [-d|--debug] [-h|--help]";

static std::string TMFILE, INPUTFILE = "";
static bool HELP = false, DEBUG = false;

static void parseArgs(int argc, char** argv);

/*-------- MAIN --------*/

int main(int argc, char** argv) {
  parseArgs(argc, argv);
  if (HELP) {
    std::cout << USAGE << std::endl;
    std::exit(0);
  }
  turmac::Parser parser = turmac::Parser(TMFILE);
  std::ifstream inputFile(INPUTFILE);
  std::string tmInputContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
  try {
    turmac::TuringMachine tm = parser.parse();
    std::cout << "running turing machine: " + TMFILE << std::endl;
    tm.setTape(tmInputContent);
    std::string input;
    std::cout << tm.toString();
    while (!tm.isHalted() && (!DEBUG || getline(std::cin, input))) {
      if (!DEBUG)
        std::cout << std::endl;
      tm.next(1);
      std::cout << tm.toString();
    }
    std::cout << std::endl;
    if (tm.isHalted())
      std::cout << "halted: " << (tm.isAccepting() ? "accepting" : "rejecting") << std::endl;
  } catch (turmac::ParseException& e) {
    std::cerr << e.what() << std::endl;
  }
  exit(0);
}


/*-------- METHOD IMPLEMENTATION --------*/

static void parseArgs(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    //set variables accordingly
    if (arg == "-h" || arg == "--help")
      HELP = true;
    else if (arg == "-d" || arg == "--debug")
      DEBUG = true;
    else if (TMFILE.empty() || TMFILE.length() == 0)
      TMFILE = arg;
    else if (INPUTFILE.empty() || INPUTFILE.length() == 0)
      INPUTFILE = arg;
    else {
      std::cerr << "unrecognised argument: " << arg << std::endl;
      std::cerr << USAGE << std::endl;
      std::exit(1);
    }
  }
  //check that a file was specified
  if (!HELP) {
    if (TMFILE.empty() || TMFILE.length() == 0) {
      TMFILE = argv[0];
      std::cerr << "expected tm file argument" << std::endl;
      std::cerr << USAGE << std::endl;
      exit(1);
    } else if (INPUTFILE.empty() || INPUTFILE.length() == 0) {
      INPUTFILE = argv[1];
      std::cerr << "expected input text file argument" << std::endl;
      std::cerr << USAGE << std::endl;
      exit(1);
    }
  }
}