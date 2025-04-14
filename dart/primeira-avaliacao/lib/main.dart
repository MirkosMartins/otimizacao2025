import 'package:flutter/material.dart';
import 'package:fl_chart/fl_chart.dart';
import 'package:flutter/services.dart' show rootBundle;
import 'reta.dart';
import 'io.dart';


void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Gráficos de Interseção'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<List<int>> retas = [];
  List<List<double>> intersecoes = [];
  bool isLoading = true;
  bool generatedLines = true;
  IO io = IO();

  @override
  void initState(){
    super.initState();
    List<Reta> retasGeradas = io.generateRetas(10);
    io.escreverRetas(retasGeradas, () {
      setState(() {
        generatedLines = false;
      });
    });
    carregarDados();
  }

  List<List<double>> calcularExtremos(List<int> a, List<int> b, double limite) {
  double dx = (b[0] - a[0]).toDouble();
  double dy = (b[1] - a[1]).toDouble();

  if (dx == 0) {
    // Reta vertical
    return [
      [a[0].toDouble(), -limite],
      [a[0].toDouble(), limite],
    ];
  } else if (dy == 0) {
    // Reta horizontal
    return [
      [-limite, a[1].toDouble()],
      [limite, a[1].toDouble()],
    ];
  } else {
    // Reta inclinada
    double m = dy / dx; // Inclinação
    double c = a[1] - m * a[0]; // Interseção com o eixo y

    // Calcula os extremos
    return [
      [-limite, m * -limite + c], // Ponto na borda esquerda
      [limite, m * limite + c],   // Ponto na borda direita
    ];
  }
}

  Future<void> carregarDados() async {
    List<Reta> retasCarregadas = await lerRetas();
    List<List<int>> retasTemp = [];
    List<List<double>> intersecoesTemp = [];
    double limite = 12.0;

    for (int i = 0; i < retasCarregadas.length; i++) {
      for (int j = i + 1; j < retasCarregadas.length; j++) {
        List<double>? intersection = encontrarIntersecao(
          retasCarregadas[i].a,
          retasCarregadas[i].b,
          retasCarregadas[j].a,
          retasCarregadas[j].b
        );
        if (intersection != null) {
          intersecoesTemp.add(intersection);
        }
      }

      List<List<double>> extremos = calcularExtremos(
        retasCarregadas[i].a, retasCarregadas[i].b, limite);

      retasTemp.add([
        extremos[0][0].toInt(),
        extremos[0][1].toInt(),
        extremos[1][0].toInt(),
        extremos[1][1].toInt(),
      ]);
    }

    setState(() {
      retas = retasTemp;
      intersecoes = intersecoesTemp;
      isLoading = false;
    });
  }

  List<double>? encontrarIntersecao(
    List<int> a, List<int> b, List<int> c, List<int> d) {
    int det = (b[0] - a[0]) * (d[1] - c[1]) - (b[1] - a[1]) * (d[0] - c[0]);

    if (det == 0) {
      print('${a}, ${b}, ${c}, ${d}: não são paralelas');
      return null;
    }

    double t = ((c[0] - a[0]) * (d[1] - c[1]) - (c[1] - a[1]) * (d[0] - c[0])) /
        det;

    double px = a[0] + t * (b[0] - a[0]);
    double py = a[1] + t * (b[1] - a[1]);

    print('${a}, ${b}, ${c}, ${d}: ${px.toStringAsFixed(4)}, ${py.toStringAsFixed(4)}');
    return [px, py];
  }

  Future<List<Reta>> lerRetas() async {
    List<Reta> retas = [];
    String fileContent = await rootBundle.loadString('assets/input.txt');
    List<String> lines = fileContent.split('\n');
    
    for (String line in lines) {
      List<String> coords = line.split(' ');
      List<String> coords1 = coords[0].split(',');
      List<String> coords2 = coords[1].split(',');
      List<int> a = [int.parse(coords1[0]), int.parse(coords1[1])];
      List<int> b = [int.parse(coords2[0]), int.parse(coords2[1])];
      retas.add(Reta(a, b));
    }
    return retas;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: isLoading
            ? const CircularProgressIndicator()
            : AspectRatio(
                aspectRatio: 2,
                child: LineChart(
                  LineChartData(
                    lineBarsData: [
                      for (var reta in retas)
                        LineChartBarData(
                          spots: [
                            FlSpot(reta[0].toDouble(), reta[1].toDouble()),
                            FlSpot(reta[2].toDouble(), reta[3].toDouble()),
                          ],
                          isCurved: false,
                          colors: [Colors.blue],
                          barWidth: 1,
                        ),
                      LineChartBarData(
                        spots: intersecoes
                            .map((ponto) => FlSpot(ponto[0], ponto[1]))
                            .toList(),
                        colors: [Colors.green],
                        barWidth: 0,
                        dotData: FlDotData(show: true),
                      ),
                    ],
                  ),
                ),
              ),
      ),
    );
  }
}
