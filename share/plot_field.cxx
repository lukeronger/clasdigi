Int_t plot_field(double x_plane = 100){

   clas12::mag::CLAS12MagneticField * mf = new clas12::mag::CLAS12MagneticField();

   Int_t  nZbins = 500;
   Int_t  nXbins = 500;

   TH2F * hBx = new TH2F("hBx","CLAS 12 magnetic field - Bx",nZbins,-100,600,nXbins,-400,400);
   TH2F * hBy = new TH2F("hBy","CLAS 12 magnetic field - By",nZbins,-100,600,nXbins,-400,400);
   TH2F * hBz = new TH2F("hBz","CLAS 12 magnetic field - Bz",nZbins,-100,600,nXbins,-400,400);
   TH2F * hBperp = new TH2F("hBperp","CLAS 12 magnetic field - BT", nZbins,-100,600,nXbins,-400,400);


   for(int i=1;i<=nZbins; i++){
      for(int j=1;j<=nXbins; j++){

         Int_t bin = hBx->GetBin(i,j);

         double x = x_plane;
         double y = hBx->GetYaxis()->GetBinCenter(j);
         double z = hBx->GetXaxis()->GetBinCenter(i);

         TEveVector B = mf->GetFieldD(x,y,z);

         hBx->SetBinContent( bin, B.fX );
         hBy->SetBinContent( bin, B.fY );
         hBz->SetBinContent( bin, B.fZ );
         hBperp->SetBinContent( bin, TMath::Sqrt(B.fX*B.fX + B.fY*B.fY));


      }
   }

   TCanvas * c = new TCanvas();
   c->Divide(2,2);

   c->cd(1);
   hBx->Draw("colz");

   c->cd(2);
   hBy->Draw("colz");

   c->cd(3);
   hBz->Draw("colz");

   c->cd(4);
   hBperp->Draw("colz");


   return 0;
}
