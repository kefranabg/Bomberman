//
// AObject.hh for AObject.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 16:05:00 2014 LOEB Thomas
// Last update Fri Jun 13 17:24:34 2014 Maxime Manzano
//

#ifndef			AOBJECT_HH_
# define		AOBJECT_HH_

# include		<glm/glm.hpp>
# include		<glm/gtc/matrix_transform.hpp>
# include		<AShader.hh>
# include		<Clock.hh>
# include		<Texture.hh>
# include		<Geometry.hh>
# include		<Model.hh>

class			AObject {
protected:
  glm::vec3		_position;
  glm::vec3		_rotation;
  glm::vec3		_scale;
  glm::vec3		_coord;
  gdl::Texture		_texture;
  gdl::Geometry		_geometry;
  gdl::Model		_model;
  int			_idx;
  bool			_anim;
  std::vector<std::string> _animations;

public:
  AObject();
  AObject(bool);
  virtual ~AObject();
  virtual bool		initialize(glm::vec3 const &) = 0;
  virtual void		draw(gdl::AShader &, gdl::Clock const &) = 0;
  void			setCurrentAnim(int, bool);
  int			getIdx() const;
  void			setIdx(int);
  void			translate(glm::vec3 const &);
  void			rotate(glm::vec3 const&, float);
  glm::mat4		getTransformation();
  glm::vec3		getPosition() const;
  glm::vec3		getRotation() const;
  glm::vec3		getScale() const;
  glm::vec3		getCoord() const;
  void			setCoord(glm::vec3 const &);
  void			setScale(glm::vec3 const &);
  void			setRotation(glm::vec3 const &);
};

#endif			/* AOBJECT_HH_ */
