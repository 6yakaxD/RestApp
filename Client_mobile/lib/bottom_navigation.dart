import 'package:restapp/screens/Fav/favourite_page.dart';
import 'package:restapp/screens/Menu/menu_page.dart';
import 'package:restapp/screens/Prof/profile_page.dart';
import 'package:flutter/material.dart';
import 'package:google_nav_bar/google_nav_bar.dart';
import 'package:line_icons/line_icons.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {

  int _selectedIndex = 0;

  final List<Widget> _pages = [
    const MenuPage(),
    const FavouritePage(),
    const ProfilePage(),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(

      body: _pages[_selectedIndex],

      bottomNavigationBar: Container(
        color: const Color.fromARGB(255, 45, 45, 45),
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 15, vertical: 20),
          child: GNav(

            gap: 10,
            backgroundColor: const Color.fromARGB(255, 45, 45, 45),
            color: Colors.white,
            activeColor: Color.fromARGB(255, 219, 104, 10), // Изменено на Colors.red
            tabBackgroundColor: Color.fromARGB(255, 18, 18, 18),
            padding: const EdgeInsets.all(16),

            selectedIndex: _selectedIndex,
            onTabChange: (index){
              setState(() {
                _selectedIndex = index;
              });
            },

            tabs: const [
              GButton(
                icon: LineIcons.home,
                text: 'Home',
              ),
              GButton(
                icon: LineIcons.heart,
                text: 'Likes',
              ),
              GButton(
                icon: LineIcons.user,
                text: 'Profile',
              )
            ],
            
          ),
        ),
      )

    );

  }


}