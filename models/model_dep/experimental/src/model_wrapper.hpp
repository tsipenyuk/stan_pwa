#ifndef SRC__STRUCTURES__MODEL_MODEL_WRAPPER_HPP
#define SRC__STRUCTURES__MODEL_MODEL_WRAPPER_HPP

#include <stan_pwa/src/complex.hpp>
#include <stan_pwa/src/model_inst.hpp>
#include <stan_pwa/src/typedefs.h>

namespace stan_pwa {

  // Define pointers to vector amplitudes depending on the symmetry of the
  // model
  template <typename T>
  using APTR_t = C_t<T> (Model::*) (const unsigned int, const Var_t<T>&);

  template <typename T>
  using AVPTR_t = CV_t<T> (Model::*) (const Var_t<T>&);

  // By default, point to the symmetric model
  template <typename T>
  APTR_t<T> amp_ptr=&Model::amplitude_sym;
  template <typename T>
  AVPTR_t<T> amp_vector_ptr=&Model::amplitude_vector_sym;

  template <typename T>
  class Wrapper {
  public:
    Wrapper(bool a_sym_flag,
	    APTR_t<T> a_amp_ptr,
	    AVPTR_t<T> a_amp_vector_ptr)
    {
      if (a_sym_flag == 0) {
	  a_amp_ptr = &Model::amplitude;
	  a_amp_vector_ptr = &Model::amplitude_vector;
      } // end if
    };    
  };

}

namespace stan {
  namespace math {

  template <typename T>
  stan_pwa::Wrapper<T> ModelWrapper(stan_pwa::sym_flag,
				    stan_pwa::amp_ptr<T>,
				    stan_pwa::amp_vector_ptr<T>);


  template <typename T>
  inline
  std::vector<typename boost::math::tools::promote_arg<T>::type>
  amplitude(const unsigned int &res_id, const Var_t<T>& y) {
//    return (stan_pwa::My_model.*stan_pwa::amp_ptr<T>)(res_id, y);
return stan_pwa::My_model.amplitude(res_id, y);
  }


    template <typename T0>
    inline
    std::vector<Eigen::Matrix<typename boost::math::tools::promote_args<T0>::type, Eigen::Dynamic, 1> >
    amplitude_vector(const Eigen::Matrix<T0, Eigen::Dynamic,1>& y) 
    {
//      return (stan_pwa::My_model.*stan_pwa::amp_vector_ptr<T0>)(y);
      return stan_pwa::My_model.amplitude_vector<T0>(y);
    }


  template <typename T0, typename T1>
  typename boost::math::tools::promote_args<T0,T1>::type ///> return scalar   
  f_genfit(const CV_t<T0>& x, const CV_t<T1>& y) {
    return stan_pwa::My_model.f_genfit(x,y);
  };


    
    inline int num_resonances() {
      return stan_pwa::My_model.get_num_res();
    }


    inline int num_variables() {
      return stan_pwa::My_model.get_num_var();
    }

  }
}






#endif


