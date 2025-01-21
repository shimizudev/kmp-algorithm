#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

class KMP {
private:
    static void printBanner() {
        std::cout << MAGENTA;
        std::cout << R"(
╔═══════════════════════════════════════════╗
║     ╦╔═╔╦╗╔═╗  ╔═╗╦  ╔═╗╔═╗╦═╗╦╔╦╗╦ ╦╔╦╗ ║
║     ╠╩╗║║║╠═╝  ╠═╣║  ║ ╦║ ║╠╦╝║ ║ ╠═╣║║║ ║
║     ╩ ╩╩ ╩╩    ╩ ╩╩═╝╚═╝╚═╝╩╚═╩ ╩ ╩ ╩╩ ╩ ║
╚═══════════════════════════════════════════╝)" << RESET << "\n";
    }

    static std::vector<int> computeLPS(const std::string& pattern) {
        int m = pattern.length();
        std::vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

public:
    static std::vector<int> search(const std::string& text, const std::string& pattern) {
        std::vector<int> occurrences;
        if (pattern.empty() || text.empty()) {
            return occurrences;
        }
        int n = text.length();
        int m = pattern.length();
        std::vector<int> lps = computeLPS(pattern);
        int i = 0;
        int j = 0;
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            if (j == m) {
                occurrences.push_back(i - j);
                j = lps[j - 1];
            }
            else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        return occurrences;
    }

    static void printMatches(const std::string& text, const std::string& pattern) {
        printBanner();
        std::vector<int> positions = search(text, pattern);

        std::cout << CYAN << "╭" << std::string(50, '─') << "╮\n";
        std::cout << "│ " << YELLOW << "Pattern found " << GREEN << positions.size()
            << YELLOW << " times at positions: ";
        for (int pos : positions) {
            std::cout << GREEN << pos << " ";
        }
        std::cout << CYAN << std::string(50 - positions.size() * 3, ' ') << "│\n";
        std::cout << "╰" << std::string(50, '─') << "╯\n" << RESET;

        std::cout << "\n" << BLUE << "Pattern Matching Visualization:\n" << RESET;
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

        std::cout << CYAN << "Text:    " << RESET;
        for (size_t i = 0; i < text.length(); i++) {
            std::cout << text[i] << " ";
        }
        std::cout << "\n" << std::string(9, ' ');
        for (size_t i = 0; i < text.length(); i++) {
            std::cout << BLUE << i % 10 << " ";
        }
        std::cout << RESET << "\n\n";

        for (int pos : positions) {
            std::cout << std::string(9, ' ');
            for (size_t i = 0; i < text.length(); i++) {
                if (i >= pos && i < pos + pattern.length()) {
                    std::cout << RED << "↑ " << RESET;
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << "\n" << std::string(9, ' ');
            for (size_t i = 0; i < text.length(); i++) {
                if (i >= pos && i < pos + pattern.length()) {
                    std::cout << GREEN << pattern[i - pos] << " " << RESET;
                }
                else {
                    std::cout << "  ";
                }
            }
            std::cout << "\n\n";
        }
    }
};

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    KMP::printMatches(text, pattern);
    return 0;
}