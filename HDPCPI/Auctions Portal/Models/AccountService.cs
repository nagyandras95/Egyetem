using System;
//using Microsoft.AspNet.Identity;
//using Microsoft.AspNet.Identity.EntityFramework;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.ComponentModel.DataAnnotations;
using System.Web;

namespace Auctions_Portal.Models
{

    public class AccountService : IAccountService
    {
        private AuctionsPortalEntities _entities;

        public AccountService()
        {
            _entities = new AuctionsPortalEntities();

            if (HttpContext.Current.Request.Cookies["user"] != null && HttpContext.Current.Session["user"] == null)
            {
                HttpContext.Current.Session["user"] = HttpContext.Current.Request.Cookies["user"]["userName"]; // felvesszük a felhasználó nevét a munkamenetbe
                HttpContext.Current.Session.Timeout = 15; // max. 15 percig él a munkamenet

                //UserCount++; // növeljük a felhasználószámot
            }
        }

        public int UserCount
        {
            get
            {
                return HttpContext.Current.Application["userCount"] == null ? 0 : 
                    (Int32)HttpContext.Current.Application["userCount"];
            }
            set
            {
                HttpContext.Current.Application["userCount"] = value;
            }
        }

        /// <summary>
        /// Get user datas.
        /// </summary>
        /// <param name="userName">The username.</param>
        public Users GetUser(String userName)
        {
            if (userName == null)
                return null;

            return _entities.Users.FirstOrDefault(c => c.UserName == userName); 
        }

        public string CurrentUserName
        {
             get { return HttpContext.Current.Session["user"] as String; }
        }

        

        public bool Login(LoginViewModel user)
        {
            if (user == null)
                return false;

            // ellenőrizzük az annotációkat
            if (!Validator.TryValidateObject(user, new ValidationContext(user, null, null), null))
                return false;

            Users guest = _entities.Users.FirstOrDefault(u => u.UserName == user.UserName); // megkeressük a felhasználót

            if (guest == null)
                return false;

            // ellenőrizzük a jelszót (ehhez a kapott jelszót hash-eljük)
            Byte[] passwordBytes = null;
            using (SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider())
            {
                passwordBytes = provider.ComputeHash(Encoding.UTF8.GetBytes(user.Password));
            }

            if (!passwordBytes.SequenceEqual(guest.Password))
                return false;

            // ha sikeres volt az ellenőrzés
            HttpContext.Current.Session["user"] = user.UserName; // felvesszük a felhasználó nevét a munkamenetbe
            HttpContext.Current.Session.Timeout = 15; // max. 15 percig él a munkamenet

            if (user.RememberLogin) // ha meg kell jegyeznünk a felhasználót
            {
                HttpCookie cookie = new HttpCookie("user"); // akkor elküldjük azt sütiként
                cookie["userName"] = user.UserName;
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

            // ha sikeres volt az ellenőrzés
            // módosítjuk a felhasználók számát
            UserCount++;

            return true;
        }

        public bool Logout()
        {
            if (HttpContext.Current.Session["user"] == null)
                return false;

            HttpContext.Current.Session["user"] = null;
            // töröljük a munkafolyamatból

            // módosítjuk a felhasználók számát
            UserCount--;

            return true;
        }

        public bool Register(UserRegistrationViewModel user)
        {
            if (user == null)
                return false;

            // ellenőrizzük az annotációkat
            if (!Validator.TryValidateObject(user, new ValidationContext(user, null, null), null))
                return false;

            if (_entities.Users.Count(c => c.UserName == user.UserName) != 0)
                return false;

            // kódoljuk a jelszót
            Byte[] passwordBytes = null;
            using (SHA512CryptoServiceProvider provider = new SHA512CryptoServiceProvider())
            {
                passwordBytes = provider.ComputeHash(Encoding.UTF8.GetBytes(user.Password));
            }

            // elmentjük a felhasználó adatait
            _entities.Users.Add(new Users
            {
                Name = user.OriginalName,
                EMail = user.EmailAdress,
                PhoneNumber = user.PhoneNumber,
                UserName = user.UserName,
                Password = passwordBytes
            });

            try
            {
                _entities.SaveChanges();
            }
            catch
            {
                return false;
            }

            return true;
        }
    }
}