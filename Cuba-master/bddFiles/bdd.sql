/*==============================================================*/
/* Nom de SGBD :  MySQL 5.0                                     */
/* Date de création :  01/12/2016 17:46:51                      */
/*==============================================================*/


drop table if exists ACTIVITE;

drop table if exists ASSOCIER;

drop table if exists AVIS_ACTIVITE;

drop table if exists AVIS_GUIDE;

drop table if exists DATE_AVIS_ACTIVITE;

drop table if exists DATE_AVIS_GUIDE;

drop table if exists GUIDE;

drop table if exists HEBERGEMENT;

drop table if exists HORRAIRE;

drop table if exists INFORMER;

drop table if exists JOUIR;

drop table if exists REGION;

drop table if exists SAISON;

drop table if exists SE_SITUER;

drop table if exists TRANSPORTS;

drop table if exists TYPE_HEBERGEMENT;

drop table if exists TYPE_TRANSPORTS;

drop table if exists USER;

/*==============================================================*/
/* Table : ACTIVITE                                             */
/*==============================================================*/
create table ACTIVITE
(
   ID_ACTIVITE          int not null,
   ID_REGION            int not null,
   LIBELLE_ACTIVITE     char(255),
   HORAIRE              time,
   DATE_ACTIVITE        date,
   ADRESSE_ACTIVITE     char(255),
   HANDICAPES_ACTIVITE  bool,
   COORDONNEES_ACTIVITE char(50),
   primary key (ID_ACTIVITE)
);

/*==============================================================*/
/* Table : ASSOCIER                                             */
/*==============================================================*/
create table ASSOCIER
(
   ID_SAISON            int not null,
   ID_HORRAIRE          int not null,
   primary key (ID_SAISON, ID_HORRAIRE)
);

/*==============================================================*/
/* Table : AVIS_ACTIVITE                                        */
/*==============================================================*/
create table AVIS_ACTIVITE
(
   ID_USER              int not null,
   ID_ACTIVITE          int not null,
   ID_DATE_AVIS_ACTIVITE int not null,
   COMMENTAIRE_ACTIVITE text,
   primary key (ID_USER, ID_ACTIVITE, ID_DATE_AVIS_ACTIVITE)
);

/*==============================================================*/
/* Table : AVIS_GUIDE                                           */
/*==============================================================*/
create table AVIS_GUIDE
(
   ID_USER              int not null,
   ID_GUIDE             int not null,
   ID_DATE_AVIS_GUIDE   int not null,
   ID_ACTIVITE          int not null,
   COMMENTAIRE_GUIDE    text,
   primary key (ID_USER, ID_GUIDE, ID_DATE_AVIS_GUIDE, ID_ACTIVITE)
);

/*==============================================================*/
/* Table : DATE_AVIS_ACTIVITE                                   */
/*==============================================================*/
create table DATE_AVIS_ACTIVITE
(
   DATE_AVIS_ACTIVITE   date,
   ID_DATE_AVIS_ACTIVITE int not null,
   primary key (ID_DATE_AVIS_ACTIVITE)
);

/*==============================================================*/
/* Table : DATE_AVIS_GUIDE                                      */
/*==============================================================*/
create table DATE_AVIS_GUIDE
(
   DATE_AVIS_GUIDE      date,
   ID_DATE_AVIS_GUIDE   int not null,
   primary key (ID_DATE_AVIS_GUIDE)
);

/*==============================================================*/
/* Table : GUIDE                                                */
/*==============================================================*/
create table GUIDE
(
   ID_GUIDE             int not null,
   NOM_GUIDE            char(255),
   PRENOM_GUIDE         char(55),
   ADRESSE_GUIDE        char(255),
   EMAIL_GUIDE          char(255),
   TEL_GUIDE            char(25),
   MDP_GUIDE            char(255),
   primary key (ID_GUIDE)
);

/*==============================================================*/
/* Table : HEBERGEMENT                                          */
/*==============================================================*/
create table HEBERGEMENT
(
   ID_HEBERGEMENT       int not null,
   ID_TYPEH             int not null,
   ID_REGION            int not null,
   HANDICAPES           bool,
   ANIMAUX              bool,
   SAISON               char(55),
   COORDONNEES_HEBERGEMENT char(55),
   primary key (ID_HEBERGEMENT)
);

/*==============================================================*/
/* Table : HORRAIRE                                             */
/*==============================================================*/
create table HORRAIRE
(
   LUNDI_MATIN_DEB      time,
   LUNDI_APREM_DEB      time,
   MARDI_MATIN_DEB      time,
   MARDI_APREM_DEB      time,
   MERCREDI_MATIN_DEB   time,
   MERCREDI_APREM_DEB   time,
   JEUDI_MATIN_DEB      time,
   JEUDI_APREM_DEB      time,
   VENDREDI_MATIN_DEB   time,
   VENDREDI_APREM_DEB   time,
   SAMEDI_APREM_DEB     time,
   SAMEDI_MATIN_DEB     time,
   DIMANCHE_MATIN_DEB   time,
   LUNDI_MATIN_FIN      time,
   LUNDI_APREM_FIN      time,
   MARDI_MATIN_FIN      time,
   MARDI_APREM_FIN      time,
   MERCREDI_MATIN_FIN   time,
   MERCREDI_APREM_FIN   time,
   JEUDI_MATIN_FIN      time,
   JEUDI_APREM_FIN      time,
   VENDREDI_MATIN_FIN   time,
   VENDREDI_APREM_FIN   time,
   SAMEDI_MATIN_FIN     time,
   SAMEDI_APREM_FIN     time,
   DIMANCHE_MATIN_FIN   time,
   DIMANCHE_APREM_FIN   time,
   ID_HORRAIRE          int not null,
   primary key (ID_HORRAIRE)
);

/*==============================================================*/
/* Table : INFORMER                                             */
/*==============================================================*/
create table INFORMER
(
   ID_GUIDE             int not null,
   ID_ACTIVITE          int not null,
   ID_REGION            int not null,
   primary key (ID_GUIDE, ID_ACTIVITE, ID_REGION)
);

/*==============================================================*/
/* Table : JOUIR                                                */
/*==============================================================*/
create table JOUIR
(
   ID_ACTIVITE          int not null,
   ID_SAISON            int not null,
   primary key (ID_ACTIVITE, ID_SAISON)
);

/*==============================================================*/
/* Table : REGION                                               */
/*==============================================================*/
create table REGION
(
   ID_REGION            int not null,
   NOM_REGION           char(55),
   primary key (ID_REGION)
);

/*==============================================================*/
/* Table : SAISON                                               */
/*==============================================================*/
create table SAISON
(
   ID_SAISON            int not null,
   DATEDEB              date,
   DATEFIN              date,
   primary key (ID_SAISON)
);

/*==============================================================*/
/* Table : SE_SITUER                                            */
/*==============================================================*/
create table SE_SITUER
(
   ID_REGION            int not null,
   ID_TRANS             int not null,
   PRIX_TRANS           char(10),
   TEMPS_TRANS          char(10),
   primary key (ID_REGION, ID_TRANS)
);

/*==============================================================*/
/* Table : TRANSPORTS                                           */
/*==============================================================*/
create table TRANSPORTS
(
   ID_TRANS             int not null,
   ID_TYPE              char(10) not null,
   LIBELE_TRANS         char(255),
   NOMCOMPAGNIE_TRANS   char(255),
   NBPASSAGERS_TRANS    int,
   HORRAIRES            time,
   HANDICAPES           bool,
   COORDONNEES_TRANSPORTS char(55),
   primary key (ID_TRANS)
);

/*==============================================================*/
/* Table : TYPE_HEBERGEMENT                                     */
/*==============================================================*/
create table TYPE_HEBERGEMENT
(
   ID_TYPEH             int not null,
   LIBELLE_TYPEH        char(255),
   CAPACITEACCUEIL_TYPEH int,
   primary key (ID_TYPEH)
);

/*==============================================================*/
/* Table : TYPE_TRANSPORTS                                      */
/*==============================================================*/
create table TYPE_TRANSPORTS
(
   ID_TYPE              char(10) not null,
   LIBELLE_TYPE         char(255),
   primary key (ID_TYPE)
);

/*==============================================================*/
/* Table : USER                                                 */
/*==============================================================*/
create table USER
(
   ID_USER              int not null,
   NOM_USER             char(55),
   PRENOM_USER          char(55),
   MDP_USER             char(255),
   AGE_USER             int,
   ADRESSE_USER         char(255),
   TEL_USER             char(25),
   primary key (ID_USER)
);

alter table ACTIVITE add constraint FK_SE_DEROULER foreign key (ID_REGION)
      references REGION (ID_REGION) on delete restrict on update restrict;

alter table ASSOCIER add constraint FK_ASSOCIER foreign key (ID_SAISON)
      references SAISON (ID_SAISON) on delete restrict on update restrict;

alter table ASSOCIER add constraint FK_ASSOCIER2 foreign key (ID_HORRAIRE)
      references HORRAIRE (ID_HORRAIRE) on delete restrict on update restrict;

alter table AVIS_ACTIVITE add constraint FK_AVIS_ACTIVITE foreign key (ID_USER)
      references USER (ID_USER) on delete restrict on update restrict;

alter table AVIS_ACTIVITE add constraint FK_AVIS_ACTIVITE2 foreign key (ID_ACTIVITE)
      references ACTIVITE (ID_ACTIVITE) on delete restrict on update restrict;

alter table AVIS_ACTIVITE add constraint FK_AVIS_ACTIVITE3 foreign key (ID_DATE_AVIS_ACTIVITE)
      references DATE_AVIS_ACTIVITE (ID_DATE_AVIS_ACTIVITE) on delete restrict on update restrict;

alter table AVIS_GUIDE add constraint FK_AVIS_GUIDE foreign key (ID_USER)
      references USER (ID_USER) on delete restrict on update restrict;

alter table AVIS_GUIDE add constraint FK_AVIS_GUIDE2 foreign key (ID_GUIDE)
      references GUIDE (ID_GUIDE) on delete restrict on update restrict;

alter table AVIS_GUIDE add constraint FK_AVIS_GUIDE3 foreign key (ID_DATE_AVIS_GUIDE)
      references DATE_AVIS_GUIDE (ID_DATE_AVIS_GUIDE) on delete restrict on update restrict;

alter table AVIS_GUIDE add constraint FK_AVIS_GUIDE4 foreign key (ID_ACTIVITE)
      references ACTIVITE (ID_ACTIVITE) on delete restrict on update restrict;

alter table HEBERGEMENT add constraint FK_DETENIR foreign key (ID_TYPEH)
      references TYPE_HEBERGEMENT (ID_TYPEH) on delete restrict on update restrict;

alter table HEBERGEMENT add constraint FK_OFFRIR foreign key (ID_REGION)
      references REGION (ID_REGION) on delete restrict on update restrict;

alter table INFORMER add constraint FK_INFORMER foreign key (ID_GUIDE)
      references GUIDE (ID_GUIDE) on delete restrict on update restrict;

alter table INFORMER add constraint FK_INFORMER2 foreign key (ID_ACTIVITE)
      references ACTIVITE (ID_ACTIVITE) on delete restrict on update restrict;

alter table INFORMER add constraint FK_INFORMER3 foreign key (ID_REGION)
      references REGION (ID_REGION) on delete restrict on update restrict;

alter table JOUIR add constraint FK_JOUIR foreign key (ID_ACTIVITE)
      references ACTIVITE (ID_ACTIVITE) on delete restrict on update restrict;

alter table JOUIR add constraint FK_JOUIR2 foreign key (ID_SAISON)
      references SAISON (ID_SAISON) on delete restrict on update restrict;

alter table SE_SITUER add constraint FK_SE_SITUER foreign key (ID_REGION)
      references REGION (ID_REGION) on delete restrict on update restrict;

alter table SE_SITUER add constraint FK_SE_SITUER2 foreign key (ID_TRANS)
      references TRANSPORTS (ID_TRANS) on delete restrict on update restrict;

alter table TRANSPORTS add constraint FK_POSSEDER foreign key (ID_TYPE)
      references TYPE_TRANSPORTS (ID_TYPE) on delete restrict on update restrict;

