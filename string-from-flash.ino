const char page_start2[] PROGMEM  = {"<!DOCTYPE html><html lang=\"en\"><head><title>NAZWA STRONY</title><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\">  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script><script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\"></script><script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\"></script></head><body><div class=\"container\"><h2>OPIS PROJEKTU</h2><p>COKOLWIEK</p><div class=\"card-deck\">"};
void printFromFlash(char *source)
{
  for (int i = 0; i <= strlen_P(source); i++)
  {
    char myChar =  pgm_read_byte_near(source + i);
    Serial.print(myChar);
  }
}
void setup() {
  Serial.begin(9600);
  printFromFlash(page_start2);
}

void loop() {
}
