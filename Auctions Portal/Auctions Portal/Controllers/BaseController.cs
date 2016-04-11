using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Auctions_Portal.Models;
using System.Web.Mvc;

namespace Auctions_Portal.Controllers
{
    public class BaseController : Controller
    {

        protected IAccountService _accountService;
        protected IAuctionService _auctionService;

        // GET: Base
        public BaseController()
        {
            _accountService = new AccountService();
            _auctionService = new AuctionService();

            // a minden oldalról elérhető információkat ise gyűjtjük
            ViewBag.Categories = _auctionService.Categories.ToList();
            ViewBag.UserCount = _accountService.UserCount;          

            if (_accountService.CurrentUserName != null)
                ViewBag.CurrentUserName = _accountService.GetUser(_accountService.CurrentUserName).Name;
        }
    }
}