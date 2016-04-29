﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AuctionsPortal.Admin.Persistence
{
        /// <summary>
        /// Perzisztencia elérhetetlenség kivétel típusa.
        /// </summary>
        public class PersistenceUnavailableException : Exception
        {
            public PersistenceUnavailableException(String message) : base(message) { }

            public PersistenceUnavailableException(Exception innerException) : base("Exception occurred.", innerException) { }
        }
}
