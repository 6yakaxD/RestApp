import 'package:restapp/screens/Menu/food_card.dart';
import 'package:flutter/material.dart';

class FoodDetailPage extends StatefulWidget {
  final Food food;
  const FoodDetailPage({
    super.key,
    required this.food,
    });

  @override
  State<FoodDetailPage> createState() => FoodDetailPageState();
}

class FoodDetailPageState extends State<FoodDetailPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color.fromARGB(255, 18, 18, 18),

      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0,
        foregroundColor: Colors.grey,
      ),

      body: Column(
        children: [
          Expanded(
          child: ListView(
            children: [
              //image
              Image.asset(widget.food.image, height: 300,),
              
              const SizedBox(height: 15),

              // name
              Padding(
                padding: const EdgeInsets.only(left: 25),
                child: Text(
                  widget.food.name,
                  style: const TextStyle(
                    color: Colors.white,
                    fontSize: 20,
                    fontWeight: FontWeight.bold),
                  ),
              ),

              const SizedBox(height: 25),

              const Padding(
                padding: EdgeInsets.only(left: 25),
                child: Text(
                  "Description",
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 18,
                    fontWeight: FontWeight.normal),
                ),
              ),
              
              //description
              Padding(
                padding: const EdgeInsets.only(left: 25, right: 15),
                child: Text(
                  widget.food.description,
                  style: const TextStyle(
                    color: Color.fromARGB(255, 155, 155, 155),
                    fontSize: 15,
                    fontWeight: FontWeight.normal,
                    height: 2),
                  ),
              ),

              
            ]
          )
        ),

        Container(
          decoration: BoxDecoration(
            color: const Color.fromARGB(255, 40, 40, 40),
            borderRadius: BorderRadius.circular(20), // установите радиус скругления
          ),
          padding: const EdgeInsets.symmetric(
            horizontal: 25,
            vertical: 15),
          child: Column(
            children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text(
                    "\$${widget.food.price}",
                    style: const TextStyle(
                      color: Colors.white,
                      fontSize: 20,
                      fontWeight: FontWeight.bold,
                    ),
                  ),

                  IconButton(
                    iconSize: 20,
                    color: Colors.white,
                    icon: const Icon(Icons.favorite),
                    onPressed: () {  },)
                ],)
              ]
            ),
          ),
        ],
      ),

      
    );
  }
}