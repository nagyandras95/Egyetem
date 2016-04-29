using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;
using System.Linq;
using System.Web.Http;
using System.Web;
using AuctionsPortal.Service.Models;

namespace AuctionsPortal.Service.Controllers
{
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
        [HttpGet]
        public IHttpActionResult Login(String userName, String password)
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

            // ha sikeres volt az ellenőrzés
            HttpContext.Current.Session["user"] = advitiser.UserName; // felvesszük a felhasználó nevét a munkamenetbe
            HttpContext.Current.Session.Timeout = 15; // max. 15 percig él a munkamenet

            if (true) // ha meg kell jegyeznünk a felhasználót
            {
                HttpCookie cookie = new HttpCookie("user"); // akkor elküldjük azt sütiként
                cookie["userName"] = advitiser.UserName;
                cookie.Expires = DateTime.Today.AddDays(365); // egy évig lesz érvényes a süti
                cookie.HttpOnly = true; // igyekszünk biztonságosság tenni a sütit
                cookie.Secure = true;
                HttpContext.Current.Response.Cookies.Add(cookie);
            }
            else // ha nem kell megjegyeznünk
            {
                // akkor kitöröljük a sütit (amennyiben volt)
                HttpCookie cookie = new HttpCookie("user");
                cookie.Expires = DateTime.MinValue; // azzal, hogy lejártnak minősítjük
                HttpContext.Current.Response.Cookies.Add(cookie);
            }

            return Ok();
        }

        [Route("logout")]
        [HttpGet]
        [Authorize] // csak bejelentklezett felhasználóknak
        public IHttpActionResult Logout()
        {
            if (HttpContext.Current.Session["user"] == null)
                return NotFound();

            HttpContext.Current.Session["user"] = null;
            // töröljük a munkafolyamatból

            return Ok();
        }

    }
}