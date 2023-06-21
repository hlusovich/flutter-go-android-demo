class User {
  final String id;
  final String name;

  final int age;
  final bool isAdmin;

  const User({required this.name, required this.age, required this.id, required this.isAdmin});

  factory User.fromJson(Map<String, dynamic> json) {
    return User(id: json['id'], name: json['name'], age: json['age'], isAdmin: json['isAdmin']);
  }

  factory User.base() {
    return const User(id: '', name: 'default', age: 18, isAdmin: false);
  }
}
