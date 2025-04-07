import 'dart:io';
import 'dart:math';

class IO {
  List<Reta> generateRetas(int n) {
    List<Reta> retas = [];
    for (int i = 0; i < n; i++) {
      int x1 = Random().nextInt(10);
      int y1 = Random().nextInt(10);
      int x2 = Random().nextInt(10);
      int y2 = Random().nextInt(10);
      retas.add(Reta([x1, y1], [x2, y2]));
    }
    return retas;
  }

  void escreverRetas(List<Reta> retas) async{
    String path = 'input.txt';
    File file = File(path);
    StringBuffer sb = StringBuffer();

    for (Reta reta in retas) {
      sb.writeln('${reta.a[0]},${reta.a[1]} ${reta.b[0]},${reta.b[1]}');
    }

    file.writeAsStringSync(sb.toString());
  }
}

class Reta {
  List<int> a;
  List<int> b;

  Reta(this.a, this.b);
}

void main(List<String> args) async{
  IO io = IO();
  List<Reta> retas = io.generateRetas(10);
  io.escreverRetas(retas);
}