import 'package:restapp/screens/Menu/food_card.dart';
import 'package:restapp/screens/Menu/food_detail_page.dart';
import 'package:flutter/material.dart';


class MenuPage extends StatefulWidget {
  const MenuPage({super.key});

  @override
  State<MenuPage> createState() => _MenuPageState();
}


class _MenuPageState extends State<MenuPage> {

  List foodMenu =[
    Food(name: "Pizza1", price: "100", description: "Its cool meat pizzssdfsdffdasdf aswd fadsfadsfgdsgqrwefweqfweqdhfqbhyudkfurayviaufayvgsdifdabsdfDBYOFSDOBC BSDVFW FSD F ASD FAS JF ASF USADU F HIAD HFI AHDIFIH ASIa", image: "assets/a.png"),
    Food(name: "Pizza2", price: "200", description: "Its cool meat pizza", image: "assets/a.png"),
    Food(name: "Pizza3", price: "300", description: "Its cool meat pizza", image: "assets/a.png"),
  ];

  // navigate to food detail page
  void navigateToFoodDetailPage (int index) {
    Navigator.push(context, MaterialPageRoute(
      builder: (context) => FoodDetailPage(food: foodMenu[index])));
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(

      backgroundColor: const Color.fromARGB(255, 18, 18, 18),

      appBar: AppBar(
        shape: const RoundedRectangleBorder(
          borderRadius: BorderRadius.only(
            topLeft: Radius.circular(0),
            topRight: Radius.circular(0),
            bottomLeft: Radius.circular(25),
            bottomRight: Radius.circular(25),
          ),
        ),
        toolbarHeight: 60,
        backgroundColor: const Color.fromARGB(255, 45, 45, 45),
        title: const Center(
          child: Text(
            "ZamZam Rest",
            style: TextStyle(color: Colors.white, fontWeight: FontWeight.bold),
          ),
        ),
      ),


      body: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          // Promo Banner

          //const SizedBox(height: 25),

          // Search Bar
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: TextField(
              style: const TextStyle(color: Colors.white),
              decoration: InputDecoration(
                hintText: "Search...",
                hintStyle: const TextStyle(color: Colors.white),
                border: OutlineInputBorder(
                  borderSide: const BorderSide(color: Colors.white),
                  borderRadius: BorderRadius.circular(20)
                  ),
                focusedBorder: const OutlineInputBorder(
                  borderSide: BorderSide(color: Colors.white),
                  //borderRadius: BorderRadius.circular(20)
                  ),
                ),
            ),
          ),

          // Menu List
          const SizedBox(height: 15),

          const Padding(
            padding: EdgeInsets.symmetric(horizontal: 25),
            child: Text("Пиццы", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
          ),

          const SizedBox(height: 10),

          SizedBox(
            height: 200,
            child: ListView.builder(
              scrollDirection: Axis.horizontal,
              itemCount: foodMenu.length,
              itemBuilder: (context, index) => FoodTile(
                food: foodMenu[index],
                onTap: () => navigateToFoodDetailPage(index),
                ),
            ),
          ),

          

          // Popular Food



        ]
      )

    );
  }
}
