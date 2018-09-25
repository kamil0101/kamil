
const String page_start = "<!DOCTYPE html><html lang=\"en\"><head><title>NAZWA STRONY</title><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\">  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script><script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\"></script><script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\"></script></head><body><div class=\"container\"><h2>OPIS PROJEKTU</h2><p>COKOLWIEK</p><div class=\"card-deck\">";
//const String c = "<div class=\"card bg-primary\"><div class=\"card-body text-center\"><p class=\"card-text\">NAZWA</p><p class=\"card-text\">WARTOSC</p> </div></div>";

const String page_end = "</div></div></body></html>";


const String par_names[6][3] = {
  {"temp_PL","temp_EN","temp_DE"},
  {"hum_PL","hum_EN","hum_DE"},
  {"prox_PL","prox_EN","prox_DE"},
  {"4_PL","4_EN","4_DE"},
  {"5_PL","5_EN","5_DE"},
  {"6_PL","6_EN","6_DE"}
};
String par_values[6] = {"13*C","13%","13"};

String buildCard(String parameter_name, String parameter_value)
{
  String temp = "<div class=\"card bg-primary\"><div class=\"card-body text-center\"><p class=\"card-text\">";
  temp += parameter_name;
  temp += "</p><p class=\"card-text\">";
  temp += parameter_value;
  temp += "</p> </div></div>";
  return temp;

}

String buildPage(int lang)
{
  String temp = page_start;
  temp += millis();
  for(int i = 0; i<6;i++)temp += buildCard(par_names[i][lang],par_values[i]);
  temp += page_end;
  temp += millis();
  return temp;
}
