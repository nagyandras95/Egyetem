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
            return View("MakeBidding");
        }

        [HttpGet]
        public ActionResult MakeBidding(Int32? itemId)
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
        public ActionResult MakeBidding(Int32? itemId, BiddingViewModel biddingAmount)
        {
            if (biddingAmount == null || biddingAmount == null)
            {
                return RedirectToAction("Index");
            }

            biddingAmount.Bidding = _auctionService.GetBidding(itemId);
            if (biddingAmount.Bidding == null)
            {
                return RedirectToAction("Index","Home");
            }

            switch(BiddingAmountValidator.Validate((Int32)itemId, biddingAmount.Bidding.Amount, biddingAmount.Amount,
                biddingAmount.Bidding.Item.StartingCall))
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

            ViewBag.Message = "Aaz ajánlatot sikeresen megtettük!";
            return View("Index", "Home");
        }
    }
}