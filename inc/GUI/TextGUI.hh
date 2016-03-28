//
// TextGUI.hh for TextGUI.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Sat Jun  7 15:16:07 2014 LOEB Thomas
// Last update Sun Jun  8 12:13:48 2014 LOEB Thomas
//

#ifndef			TEXTGUI_HH_
# define		TEXTGUI_HH_

# include               <SdlContext.hh>
# include               <glm/glm.hpp>
# include               <glm/gtc/matrix_transform.hpp>
# include               <AShader.hh>
# include               <Clock.hh>
# include               <Texture.hh>
# include               <Geometry.hh>
# include               <Model.hh>

class			TextGUI {
private:
  gdl::Geometry		_geometry;
  glm::vec3		_position;
  glm::vec3		_translate;
  glm::vec3		_rotate;
  glm::vec3		_scale;

public:
  TextGUI();
  ~TextGUI();
  bool			initialize(glm::vec3 const &, const std::string &);
  glm::vec3 const	&getPosition() const;
  void			draw(gdl::AShader &, gdl::Texture &);
  void			translate(glm::vec3 const &);
  void			rotate(glm::vec3 const &, float);
  glm::mat4		getTransformation() const;
};

#endif			/* TEXTGUI_HH_ */
