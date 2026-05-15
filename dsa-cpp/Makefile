CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

practice:
	@echo Building practice files...
	@for f in practice/*.cpp; do $(CXX) $(CXXFLAGS) -o "$${f%.cpp}" "$$f" || exit 1; done

solutions:
	@echo Building solution files...
	@for f in solutions/*.cpp; do $(CXX) $(CXXFLAGS) -o "$${f%.cpp}" "$$f" || exit 1; done

test: practice
	@echo Running practice tests...
	@for f in practice/*; do [ -x "$$f" ] && [ "$${f%.cpp}" = "$$f" ] && (echo "--- $$f ---" && "$$f" || exit 1); done
	@echo All practice tests passed!

test-solutions: solutions
	@echo Running solution tests...
	@for f in solutions/*; do [ -x "$$f" ] && [ "$${f%.cpp}" = "$$f" ] && (echo "--- $$f ---" && "$$f" || exit 1); done
	@echo All solution tests passed!

clean:
	find practice solutions -type f ! -name "*.cpp" -delete 2>/dev/null; true

.PHONY: practice solutions test test-solutions clean
