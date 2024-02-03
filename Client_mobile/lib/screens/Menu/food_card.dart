import 'dart:ui';

import 'package:flutter/material.dart';

class Food {
  String name;
  String price;
  String image;
  String description;

  Food({
    required this.name,
    required this.price,
    required this.description,
    required this.image
    });

    String get _name => name;
    String get _price => price;
    String get _description => description;
    String get _image => image;
}



class FoodTile extends StatelessWidget {
  final Food food;
  final void Function()? onTap;

  const FoodTile({
    Key? key,
    required this.food,
    required this.onTap});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: onTap,
      child: Container(
        height: 100, // Изменение высоты контейнера
        decoration: BoxDecoration(
          color: Color.fromARGB(255, 255, 255, 255),
          borderRadius: BorderRadius.circular(20),
        ),
        margin: const EdgeInsets.only(left: 15),
        padding: const EdgeInsets.all(25),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          mainAxisAlignment: MainAxisAlignment.spaceBetween, // Добавление пространства между элементами
          children: [
            Expanded(
              child: Image.asset(food.image, height: 140, fit: BoxFit.cover),
            ),
            Text(
              food.name,
              style: const TextStyle(color: Color.fromARGB(255, 40, 40, 40), fontSize: 20, fontWeight: FontWeight.bold),
            ),
            Text(
              food.price,
              style: const TextStyle(color: Color.fromARGB(255, 40, 40, 40), fontSize: 15),
            ),
          ],
        ),
      ),
    );
  }
}