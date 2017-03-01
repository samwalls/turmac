#include <turmac.h>
#include <iostream>

/*-------- CONSTANTS, VARIABLES & DECLARATIONS --------*/
static const std::string USAGE = "usage: runtm <tm-file> <input-file> [-d|--debug] [-q|--quiet] [-h|--help] [-t|--time] [-s|--space] [-n|--n-times <n>]";

static std::string TMFILE, INPUTFILE = "";
static bool HELP = false, DEBUG = false, TIME = false, SPACE = false, QUIET = false;
static unsigned int NTIMES = 1;

static void parseArgs(int argc, char** argv);

/*-------- MAIN --------*/

int main(int argc, char** argv) {
  parseArgs(argc, argv);
  if (HELP) {
    std::cout << USAGE << std::endl;
    std::exit(0);
  }
  std::ifstream inputFile(INPUTFILE);
  const std::string tmInputContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
  inputFile.close();
  std::vector<float> runTimes = std::vector<float>();
  turmac::Parser parser = turmac::Parser(TMFILE);
  turmac::TuringMachine tm = parser.parse();
  try {
    if (!QUIET) {
      std::cout << "running turing machine: " + TMFILE;
      if (NTIMES > 1)
        std::cout << " " << NTIMES << " times";
      std::cout << std::endl;
    }
    //run the turing machine NTIMES times, resetting each time
    for (unsigned int run = 0; run < NTIMES; run++) {
      tm.reset(tmInputContent);
      std::string input;
      if (!QUIET)
        std::cout << tm.toString();
      const clock_t beforeTime = clock();
      while (!tm.isHalted() && (!DEBUG || getline(std::cin, input))) {
        if (!QUIET && !DEBUG)
          std::cout << std::endl;
        tm.next(1);
        if (!QUIET)
          std::cout << tm.toString();
      }
      if (!QUIET)
        std::cout << std::endl;
      runTimes.push_back(float(clock() - beforeTime) / CLOCKS_PER_SEC);
      if ((NTIMES <= 1 || !QUIET) && tm.isHalted())
        std::cout << "halted: " << (tm.isAccepting() ? "accepting" : "rejecting") << std::endl;
    };
    //report time usage
    if (TIME) {
      if (NTIMES > 1) {
        float avgTime = runTimes[0];
        for (unsigned int i = 1; i < runTimes.size(); i++)
          avgTime += runTimes[i];
        avgTime /= runTimes.size();
        std::cout << "average time (s): " << avgTime << std::endl;
      } else {
        std::cout << "time taken (s)  : " << runTimes[0] << std::endl;
      }
    }
    //report space usage
    if (SPACE) {
      //turmac::TuringMachine is deterministic, so no need to take average space consumption
      std::cout << "input tape size : " << tmInputContent.size() << std::endl;
      std::cout << "output tape size: " << tm.getTape().size() << std::endl;
      std::cout << "diff tape size  : " << tm.getTape().size() - tmInputContent.size() << std::endl;
    }
  } catch (turmac::ParseException e) {
    std::cerr << "error when parsing: " << e.what() << std::endl;
  } catch (std::runtime_error& e) {
    std::cerr << "runtime error: " << e.what() << std::endl;
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
    else if (arg == "-t" || arg == "--time")
      TIME = true;
    else if (arg == "-s" || arg == "--space")
      SPACE = true;
    else if (arg == "-q" || arg == "--quiet")
      QUIET = true;
    else if (arg == "-n" || arg == "--n-times") {
      i++;
      if (i >= argc) {
        std::cerr << "expected argument for -n|--n-times" << std::endl;
        exit(1);
      }
      int n = std::stoi(argv[i]);
      if (n < 0) {
        std::cerr << "-n|--n-times argument cannot be negative (or higher than the maximum integer value)";
        exit(1);
      }
      NTIMES = (unsigned int)n;
    } else if (INPUTFILE.empty() || INPUTFILE.length() == 0)
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