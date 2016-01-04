extern "C" {
void setup(void);
void loop(void);
}

int main() {
  setup();
  while (1)
    loop();
}

