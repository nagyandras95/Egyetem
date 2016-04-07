using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using Auctions_Portal.Models;
using System.Web.Mvc;
using System.Text;

namespace Auctions_Portal.Controllers
{
    public class AccountController : Controller
    {

        private AuctionsPortalEntities _entities;

        public AccountController()
        {
            _entities = new AuctionsPortalEntities();

            ViewBag.Categories = _entities.Category.ToArray();
        }

        /// <summary>
        /// Registartion
        /// </summary>
        /// <returns></returns>
        [HttpGet]
        public ActionResult Index()
        {
            UserRegistrationViewModel reg = new UserRegistrationViewModel();

            return View("Index", reg);
        }


        [HttpPost]
        public ActionResult Index(UserRegistrationViewModel reg)
        {
            if(reg == null)
            {
                return RedirectToAction("Index", "Home");
            }

            /*if(String.IsNullOrEmpty(reg.OriginalName) ||
                String.IsNullOrEmpty(reg.UserName) ||
                String.IsNullOrEmpty(reg.Password) ||
                String.IsNullOrEmpty(reg.ConfirmPassword) ||
                String.IsNullOrEmpty(reg.PhoneNumber) ||
                String.IsNullOrEmpty(reg.EmailAdress))
            */
            if(!ModelState.IsValid)
            {
                ViewBag.Error = "Hiányosak a regisztrációs adatok!";
                return View("Index", reg);
            }

            if(!reg.Password.Equals(reg.ConfirmPassword))
            {
                ViewBag.Error = "A jelszó nem egyezik!";
                return View("Index", reg);
            }

            String otheruser = _entities.Users.Select(u => u.UserName).Union(_entities.Advetiser.Select(a => a.UserName))
                .FirstOrDefault(u => u.Equals(reg.UserName));
            if(otheruser != null)
            {
                ViewBag.Error = "A felhasználó név már foglalt!";
                return View("Index", reg);
            }

            SHA1CryptoServiceProvider coder = new SHA1CryptoServiceProvider();
            String pwsText = reg.Password;
            Byte[] pwdBytes = coder.ComputeHash(Encoding.UTF8.GetBytes(pwsText));

            try
            {
                Users user = new Users
                {
                    Name = reg.OriginalName,
                    UserName = reg.UserName,
                    Password = pwdBytes.ToString(),
                    EMail = reg.EmailAdress,
                    PhoneNumber = reg.PhoneNumber

                };

                _entities.Users.Add(user);
                _entities.SaveChanges();
            }
            catch
            {
                ViewBag.Error = "A regisztráció sikeretlen. Kérem, próbálja újra!";
                return View("Index", reg);
            }

            return View("Result", reg);
        }


        /// <summary>
        /// Login
        /// </summary>
        /// <returns></returns>
        [HttpGet]
        public ActionResult Login()
        {
            LoginViewModel log = new LoginViewModel();

            return View("Login", log);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Login(LoginViewModel log)
        {
            if (log == null)
            {
                return RedirectToAction("Index", "Home");
            }

            if (String.IsNullOrEmpty(log.UserName) || String.IsNullOrEmpty(log.Password))
            {
                ViewBag.Error = "Felhasználónév és jelszó megadása kötelező!";
                return View("Index", log);
            }

            Users user = _entities.Users.FirstOrDefault(u => u.UserName.Equals(log.UserName));
            if (user != null)
            {

                String pwsText = log.Password;
                
                SHA1CryptoServiceProvider coder = new SHA1CryptoServiceProvider();

                String userpwd = user.Password;
                if (!coder.ComputeHash(Encoding.UTF8.GetBytes(pwsText)).ToString().SequenceEqual(userpwd))
                {
                    ViewBag.Error = "Nem megfelelőek a bejelenktezési adatok!";
                    return RedirectToAction("Index", "Home");
                }

                
            }
            else
            {
                ViewBag.Error = "Nem megfelelőek a bejelenktezési adatok!";
                return RedirectToAction("Index", "Home");
            }


            Session["user"] = log.UserName;
            Session.Timeout = 15;

            return View("Index", "Home");

        }
    }
}
 