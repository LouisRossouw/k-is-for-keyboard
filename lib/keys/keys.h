#ifndef KEYS_H
#define KEYS_H

class Keys {
public:
  Keys(int rows, int cols);

  void begin();
  void loop();

private:
  int _rows;
  int _cols;
};

#endif