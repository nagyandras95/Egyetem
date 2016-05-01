using System;
using System.Security.Cryptography;
using System.Text;
using System.Linq;
using System.Web.Http;
using System.Web;
using AuctionsPortal.Data;
using AuctionsPortal.Service.Models;

namespace AuctionsPortal.Service.Controllers
{
    [RoutePrefix("api/account")] 
    public class AccountController : ApiController
    {
        private AuctionsPortalEntities _entities;

        public AccountController()
        {
            _entities = new AuctionsPortalEntities();
        }

        ~AccountController()
        {
            Dispose(false);
        }

        [Route("login/{userName}/{password}")]
        [System.Web.Http.HttpGet]
        public IHttpActionResult Login(String userName,String password)
        {

           
          Advetiser advitiser = _entities.Advetiser.FirstOrDefault(a => a.UserName == userName); // megkeressük a felhasználót

            if (advitiser == null)
                return NotFound();            

            // ellenőrizzük a jelszót (ehhez a kapott jelszót hash-eljük)
            Byte[] passwordBytes = null;
            using (SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider())
            {
                passwordBytes = provider.ComputeHash(Encoding.UTF8.GetBytes(password));
            }

            if (!passwordBytes.SequenceEqual(advitiser.Password))
                return NotFound();

            if (HttpContext.Current.Session["user"] != null)
                HttpContext.Current.Session["user"] = null;

                // ha sikeres volt az ellenőrzés
            HttpContext.Current.Session["user"] = advitiser.UserName; // felvesszük a felhasználó nevét a munkamenetbe
            HttpContext.Current.Session.Timeout = 15; // max. 15 percig él a munkamenet
            return Ok();
        }

        [Route("logout")]
        [System.Web.Http.HttpGet]
        [Authorize] // csak bejelentklezett felhasználóknak
        public IHttpActionResult Logout()
        {
            if (HttpContext.Current.Session["user"] == null)
                return NotFound();

            HttpContext.Current.Session["user"] = null;
            // töröljük a munkafolyamatból

            return Ok();
        }

        /// <summary>
        /// Új hírdető hozzáadása
        /// </summary>
        /// <param name="advatiserDTO"></param>
        /// <returns></returns>
        [Route("login/{advatiserDTO}")]
        [Authorize]
        [System.Web.Http.HttpGet]
        public IHttpActionResult Register([FromBody] AdvatiserDTO advatiserDTO)
        {
            Advetiser advitiser = _entities.Advetiser.FirstOrDefault(a => a.UserName == advatiserDTO.UsnerName);

            if (advitiser != null) ;

            SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider();
            try
            {
                 Advetiser addedAdvatiser = _entities.Advetiser.Add(new Advetiser
                 {
                        Name = advatiserDTO.Name,
                        UserName = advatiserDTO.UsnerName,
                        Password = provider.ComputeHash(Encoding.UTF8.GetBytes(advatiserDTO.Password))
                 });

                    _entities.SaveChanges(); // elmentjük az új hírdetőt

                    // visszaküldjük a létrehozott hírdetőt
                    return Created(Request.RequestUri + advatiserDTO.UsnerName, advatiserDTO);
                }
                catch
                {
                    return InternalServerError();
                }
        }



    }
}