#include <exception>
#include <iostream>

namespace {
class myException : std::exception {
  virtual const char *what() const noexcept { return "myException happened"; }
};
}

class Magician {
public:
  int magic() const noexcept {
    std::cout << "Execute me\n";
    return _magic;
  }                                // marked as not throwing
  void doMagic() noexcept(false) { // marked as possibly throwing
    if (_magic < 500) {
      throw myException();
    }
  }
  void exceptionFreeMagic() noexcept {
    /** do some magic */
  }

  void badMagic() noexcept {
      // putting a throw-statement inside this function will NOT break compilation
      // even if it violates the noexcept specifier
      throw myException();
  }

  void unspecifiedMagic() { /** do some more magic **/
  }

private:
  int _magic{1000};
};

int main(int argc, char **argv) {
  Magician m;

  // does NOT execute magic!
  static_assert(noexcept(m.magic()), "magic is noexcept");
  static_assert(
      noexcept(m.exceptionFreeMagic()),
      "this magic is exception free"); // does NOT execute the function
  static_assert(!noexcept(m.doMagic()), "magic is noexcept"); //
  static_assert(!noexcept(m.unspecifiedMagic()),
                "unspecified functions are possibly throwing");
  static_assert(noexcept(m.badMagic()),
                "bad magic pretends to be not throwing");

}
