//
// GetGDL.hh for GetGDL.hh in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Wed Jun  4 16:54:39 2014 LOEB Thomas
// Last update Thu Jun  5 12:52:40 2014 LOEB Thomas
//

#ifndef			GETGDL_HH_
# define		GETGDL_HH_

# include		<SdlContext.hh>

class			GetGDL : public gdl::SdlContext {
public:
  GetGDL();
  virtual ~GetGDL();
  SDL_Window		*getWindow() const;
};

#endif			/* GETGDL_HH_ */
