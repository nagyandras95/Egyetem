using System.Linq;
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

            ViewBag.ListNumber = _auctionService.GetTimesOfAdvertisments(20);
            ViewBag.CurrentCategory = 0;          

            if (_accountService.CurrentUserName != null)
            {
                ViewBag.CurrentUserName = _accountService.GetUser(_accountService.CurrentUserName).Name;
                ViewBag.CurrentUserId = _accountService.GetUser(_accountService.CurrentUserName).UserId;
            }
                
        }
    }
}