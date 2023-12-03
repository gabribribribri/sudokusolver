#include <array>
#include <bitset>
#include <iostream>
#include <vector>

using Board = std::vector<std::vector<char>>;

void printBoard(const Board &board) noexcept {
  for (auto row : board) {
    for (auto ch : row) {
      std::cout << ch << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

class SudokuSolver {

public:

  SudokuSolver(Board &board) : m_Board(board) {}

  void solve() {
    for (size_t row = 0; row < 9; row++) {
      for (size_t col = 0; col < 9; col++) {
        if (m_Board[row][col] != '.') {
          size_t digit_idx = m_Board[row][col] - '1';
          m_Row_Contains[row].set(digit_idx);
          m_Col_Contains[col].set(digit_idx);
          m_Cell_Contains[get_cell(row, col)].set(digit_idx);
        }
      }
    }
    internal_solve(0, 0);
  }

private:

  Board &m_Board;
  std::array<std::bitset<9>, 9> m_Row_Contains;
  std::array<std::bitset<9>, 9> m_Col_Contains;
  std::array<std::bitset<9>, 9> m_Cell_Contains;

  bool internal_solve(size_t start_row, size_t start_col) noexcept {
    auto [row, col] = next_empty_position(start_row, start_col);

    if (row == 9) {
      return true;
    }

    size_t cell = get_cell(row, col);

    std::bitset<9> contains =
        m_Row_Contains[row] | m_Col_Contains[col] | m_Cell_Contains[cell];

    if (contains.all()) {
      return false;
    }

    for (size_t digit_idx = 0; digit_idx < 9; digit_idx++) {
      if (!contains[digit_idx]) {
        m_Board[row][col] = static_cast<char>(digit_idx + '1');
        m_Row_Contains[row].set(digit_idx);
        m_Col_Contains[col].set(digit_idx);
        m_Cell_Contains[cell].set(digit_idx);
        if (internal_solve(row, col)) {
          return true;
        } // else
        m_Row_Contains[row].reset(digit_idx);
        m_Col_Contains[col].reset(digit_idx);
        m_Cell_Contains[cell].reset(digit_idx);
      }
    }
    m_Board[row][col] = '.';
    return false;
  }

  std::pair<size_t, size_t> next_empty_position(size_t row,
                                                size_t col) const noexcept {
    size_t cur_col = col;
    size_t cur_row = row;
    for (; cur_row < 9; cur_row++) {
      for (; cur_col < 9; cur_col++) {
        if (m_Board[cur_row][cur_col] == '.') {
          return {cur_row, cur_col};
        }
      }
      cur_col = 0;
    }
    return {9, 9}; // next position not found
  }

  constexpr std::size_t get_cell(std::size_t row, std::size_t col) noexcept {
    return (row / 3) * 3 + col / 3;
  }
};

class Solution {
public:
  void solveSudoku(std::vector<std::vector<char>> &board) const noexcept {
    SudokuSolver s(board);
    s.solve();
  }
};
