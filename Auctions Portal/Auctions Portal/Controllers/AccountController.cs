using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using Auctions_Portal.Models;
using System.Web.Mvc;
using System.Text;

namespace Auctions_Portal.Controllers
{
    public class AccountController : BaseController
    {

        public ActionResult Index()
        {

            return RedirectToAction("Login");
        }

        /// <summary>
        /// Login.
        /// </summary>
        [HttpGet]
        public ActionResult Login()
        {
            return View("Login");
        }

        /// <summary>
        /// Bejelentkezés.
        /// </summary>
        /// <param name="user">A bejelentkezés adatai.</param>
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Login(LoginViewModel user)
        {
            if (!ModelState.IsValid)
                return View("Login", user);

            // bejelentkeztetjük a felhasználót
            if (!_accountService.Login(user))
            {
                // nem szeretnénk, ha a felhasználó tudná, hogy a felhasználónévvel, vagy a jelszóval van-e baj, így csak általános hibát jelzünk
                ModelState.AddModelError("", "Hibás felhasználónév, vagy jelszó.");
                return View("Login", user);
            }

            return RedirectToAction("Index", "Home"); // átirányítjuk a főoldalra
        }

        /// <summary>
        /// Registartion.
        /// </summary>
        [HttpGet]
        public ActionResult Register()
        {
            return View("Register");
        }


        /// <summary>
        /// Regisztráció.
        /// </summary>
        /// <param name="guest">Regisztrációs adatok.</param>
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Register(UserRegistrationViewModel guest)
        {
            // végrehajtjuk az ellenőrzéseket
            if (!ModelState.IsValid)
                return View("Register", guest);

            if (!_accountService.Register(guest))
            {
                ModelState.AddModelError("UserName", "A megadott felhasználónév már létezik.");
                return View("Register", guest);
            }

            _accountService.Logout(); // ha már volt valaki bejelentkezve, kijelentkeztetjük

            ViewBag.Information = "A regisztráció sikeres volt. Kérjük, jelentkezzen be.";

            return RedirectToAction("Login");
        }
    }
}
 