using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Auctions_Portal.Models;

namespace Auctions_Portal.Controllers
{
    public class BiddingController : BaseController
    {
        // GET: Bidding
        public ActionResult Index()
        {
            return View("Index");
        }

        [HttpGet]
        public ActionResult Index(Int32? itemId)
        {
            if (itemId == null)
            {
                return RedirectToAction("Index");
            }

            BiddingViewModel biddingAmount = _auctionService.NewBidding(itemId);
            if (biddingAmount == null)
            {
                return RedirectToAction("Index");
            }

            return View("Index", biddingAmount);
            

        }

        [HttpPost]
        public ActionResult Index(Int32? itemId, BiddingViewModel biddingAmount)
        {
            if (itemId == null || biddingAmount == null)
            {
                return RedirectToAction("Index");
            }

            Item item = _auctionService.GetItem(itemId);
            Int32? lastAmount = _auctionService.GetLastAmount(itemId);
            if (lastAmount == null || item == null)
                return RedirectToAction("Index", "Home");

            biddingAmount.Item = item;

            switch(BiddingAmountValidator.Validate(item.StartingCall, (Int32)lastAmount, biddingAmount.Amount))
            {
                case BiddingAmountError.TooFew :
                    ModelState.AddModelError("BiddingAmount", "Túl alacsony ajálat!");   
                    break;
                
            }

            if (!ModelState.IsValid)
                return View("Index", biddingAmount);

            if(_accountService.CurrentUserName == null)
            {
                return RedirectToAction("Index","Home");
                
            }

            String userName = _accountService.CurrentUserName;

            if (!_auctionService.SaveBidding(itemId, userName, biddingAmount))
            {
                ModelState.AddModelError("", "A ajánlattétel sikertelen volt, kérem, próbálja újra!");
                return View("Index", biddingAmount);
            }

            return View("Result", biddingAmount);
        }
    }
}