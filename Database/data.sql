-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1
-- Généré le : mer. 04 août 2021 à 00:59
-- Version du serveur :  10.4.18-MariaDB
-- Version de PHP : 8.0.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `astronomy`
--

-- --------------------------------------------------------

--
-- Structure de la table `categories`
--

CREATE TABLE `categories` (
  `category_id` int(11) UNSIGNED NOT NULL,
  `category_name` varchar(256) DEFAULT NULL,
  `category_description` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `categories`
--

INSERT INTO `categories` (`category_id`, `category_name`, `category_description`) VALUES
(1, 'Etoile', 'Une étoile est un objet céleste de forme sphérique, constitué essentiellement de plasma, et dont la structure est modelée par la gravité. Lors de sa formation, une étoile est essentiellement composée d’hydrogène et d’hélium. Durant la majeure partie de son existence, son cœur est le siège de réactions de fusion nucléaire, dont une partie de l’énergie est rayonnée sous forme de lumière. La matière qui la compose s’en trouve presque complètement ionisée.'),
(2, 'Etoile variable', 'En astronomie, une étoile variable est une étoile dont l\'éclat varie au cours de périodes plus ou moins longues.'),
(3, 'Etoile double', 'Une étoile double est une paire d\'étoiles qui apparaissent comme proches l\'une de l\'autre.\r\n\r\nCeci peut se produire :\r\n\r\n- parce que la paire forme un système binaire d\'étoiles en orbites mutuelles liées gravitationnellement l\'une à l\'autre ;\r\n- parce que la paire d\'étoiles forme une « double optique », un alignement dû au hasard de deux étoiles, qui se trouvent dans le ciel à des distances différentes, mais qui sont vues sous le même angle de visée depuis la Terre.'),
(4, 'Etoile carbonée', 'Les étoiles carbonées sont des étoiles qui ont développé une composition chimique où le carbone domine à la place de l\'oxygène.'),
(5, 'Amas ouvert', 'Un amas ouvert est un amas stellaire groupant environ de 100 à 10 000 étoiles liées par la gravitation. Les amas ouverts sont peu lumineux et s’observent essentiellement dans notre Galaxie, où ils se situent dans le plan galactique'),
(6, 'Amas globulaire', 'En astronomie, un amas globulaire est un amas stellaire très dense, contenant typiquement une centaine de milliers d\'étoiles distribuées dans une sphère dont la taille varie d\'une vingtaine à quelques centaines d\'années-lumière. Leur densité est ainsi nettement plus élevée que celle des amas ouverts.'),
(7, 'Astérisme', 'En astronomie, un astérisme est une figure remarquable dessinée par des étoiles particulièrement brillantes. En général, ces étoiles ne sont liées ni par une interaction gravitationnelle significative, ni par une gestation commune, ce qui fait d\'un astérisme un objet céleste plutôt arbitraire et subjectif.'),
(8, 'Galaxie satellite', 'Dans une paire de galaxies en orbite, si l\'une est nettement plus grande que l\'autre, alors, la plus grosse est la galaxie primaire et la plus petite, la galaxie satellite.'),
(9, 'Galaxie spirale', 'Une galaxie spirale est un type de galaxie contenant jusqu\'à plusieurs centaines de milliards d\'étoiles et qui adopte la forme aplatie d\'un disque, avec un renflement central sphérique lumineux appelé le bulbe. Les galaxies spirales contiennent également des quantités importantes de gaz et de poussières. Autour du disque, il existe également un halo moins dense et plus discret, aux étoiles fréquemment regroupées en amas globulaires.'),
(10, 'Galaxie compacte', 'Une galaxie compacte est une galaxie naine contenant de grands amas stellaires composés d\'étoiles jeunes, chaudes et massives donnant à l\'ensemble une couleur dominante bleue. Dans la mesure où elles sont constituées d\'amas, ces galaxies n\'ont pas de forme définie'),
(11, 'Galaxie elliptique', 'Une galaxie elliptique est un type de galaxie qui regroupe des concentrations sphéroïdales de milliards d’étoiles qui ressemblent à des amas globulaires à grande échelle. Elles ont une très petite structure interne et la densité des étoiles diminue doucement du centre très lumineux vers des bords diffus.'),
(12, 'Galaxie lenticulaire', 'Les galaxies lenticulaires sont des galaxies à disque sans bras spiraux bien définis. Elles représentent la transition entre une galaxie elliptique et une galaxie spirale dans la séquence de Hubble. Formellement, elles ressemblent à des galaxies spirales dénuées de bras spiraux bien qu\'elles possèdent un bulbe galactique d\'une taille beaucoup plus importante que celui d\'une galaxie spirale standard.'),
(13, 'Amas de galaxies', 'Un amas de galaxies est l\'association de plus d\'une centaine de galaxies liées entre elles par la gravitation.'),
(14, 'Lentille gravitationnelle', 'Une lentille gravitationnelle, ou mirage gravitationnel, est produit par la présence d\'un corps céleste très massif (par exemple, un amas de galaxies) se situant entre un observateur et une source lumineuse lointaine. La lentille gravitationnelle, imprimant un fort champ gravitationnel autour d\'elle, aura comme effet de faire dévier les rayons lumineux qui passeront près d\'elle, déformant ainsi les images que recevra un observateur placé sur la ligne de visée.'),
(15, 'Nébuleuse en émission', 'En astronomie, les nébuleuses en émission sont des nuages de gaz ionisé dans le milieu interstellaire qui absorbent la lumière d\'une étoile chaude proche et la réémettent sous forme de couleurs variées à des énergies plus basses.'),
(16, 'Nébuleuse planétaire', 'Une nébuleuse planétaire est un corps céleste qui ressemble à un disque d\'aspect nébuleux. En raison de cet aspect, semblable à celui des planètes. On sait maintenant que les nébuleuses planétaires n\'ont en fait aucun rapport avec les planètes. Il s\'agit d\'une nébuleuse en émission constituée d\'une coquille de gaz en expansion éjectée d\'une étoile en fin de vie.'),
(17, 'Nébuleuse diffuse', 'En astronomie, les nébuleuses diffuses sont des nuages de matières interstellaires dispersées, constitués de gaz et de poussières mais les nébuleuses diffuses se distinguent par leurs émissions lumineuses.'),
(18, 'Nébuleuse obscure', 'Les nébuleuses obscures sont des régions où les poussières du milieu interstellaire semblent se concentrer en grands nuages qui apparaissent en régions pauvres en étoiles.\r\n\r\nLes nébuleuses sombres peuvent être vues si elles obscurcissent une partie d\'une nébuleuse en émission ou de réflexion, ou si elles bloquent la lumière des étoiles en arrière-plan.');

-- --------------------------------------------------------

--
-- Structure de la table `constellations`
--

CREATE TABLE `constellations` (
  `constellation_id` int(11) UNSIGNED NOT NULL,
  `constellation_name` varchar(256) DEFAULT NULL,
  `constellation_latin_name` varchar(256) DEFAULT NULL,
  `constellation_abreviation` varchar(3) DEFAULT NULL,
  `constellation_extent_squaredeg` float UNSIGNED DEFAULT NULL,
  `constellation_extent_percent` float UNSIGNED DEFAULT NULL,
  `constellation_right_ascension` varchar(12) DEFAULT NULL,
  `constellation_declination` varchar(12) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `constellations`
--

INSERT INTO `constellations` (`constellation_id`, `constellation_name`, `constellation_latin_name`, `constellation_abreviation`, `constellation_extent_squaredeg`, `constellation_extent_percent`, `constellation_right_ascension`, `constellation_declination`) VALUES
(1, 'Aigle', 'Aquila', 'Aql', 652.473, 1.58, '19h40m02s', '+03°24\'65\"'),
(2, 'Andromède', 'Andromeda', 'And', 722.278, 1.75, '00h48m46s', '+37°25\'91\"'),
(3, 'Autel', 'Ara', 'Ara', 237.057, 0.57, '17h22m49s	', '-56°35\'30\"'),
(4, 'Balance', 'Libra', 'Lib', 538.052, 1.3, '15h11m96s', '-15°14\'08\"'),
(5, 'Baleine', 'Cetus', 'Cet', 1231.41, 2.99, '01h40m10s', '-07°10\'76\"'),
(6, 'Bélier', 'Aries', 'Ari', 441.395, 1.07, '02h38m16s', '+20°47\'54\"'),
(7, 'Boussole', 'Pyxis', 'Pyx', 220.833, 0.54, '08h57m16s', '-27°21\'10\"'),
(8, 'Bouvier', 'Bootes', 'Boo', 906.831, 2.2, '14h42m64s	', '+31°12\'16\"'),
(9, 'Burin', 'Caelum', 'Cae', 124.865, 0.3, '04h42m27s', '-37° 52′ 90″'),
(10, 'Caméléon', 'Chamaeleon', 'Cha', 131.592, 0.32, '10h41m53s', '-79°12\'30\"'),
(11, 'Cancer', 'Cancer', 'Cnc', 505.872, 1.23, '08h38m96s', '+19°48\'35\"'),
(12, 'Capricorne', 'Capricornus', 'Cap', 413.947, 1, '21h02m93s', '-18°01\'39\"'),
(13, 'Carène', 'Carina', 'Car', 494.184, 1.2, '08h41m70s', '-63°13\'16\"'),
(14, 'Cassiopée', 'Cassiopeia', 'Cas', 598.407, 1.45, '01h19m16s', '+62°11\'04\"'),
(15, 'Centaure', 'Centaurus', 'Cen', 1060.42, 2.57, '13h04m27s', '-47°20\'72\"'),
(16, 'Céphée', 'Cepheus', 'Cep', 587.787, 1.42, '22h00m00s', '+71°00\'51\"'),
(17, 'Chevelure de Bérénice', 'Coma Berenices', 'Com', 386.475, 0.94, '12h47m27s', '+23°18\'34\"'),
(18, 'Chiens de chasse', 'Canes Venatici', 'CVn', 465.194, 1.13, '13h06m96s	', '+40°06\'11\"'),
(19, 'Cocher', 'Auriga', 'Aur', 657.438, 1.59, '06h04m42s', '+42°01\'68\"'),
(20, 'Colombe', 'Columba', 'Col', 270.184, 0.65, '05h51m76s', '-35°05\'67\"'),
(21, 'Compas', 'Circinus', 'Cir', 93.353, 0.23, '14h34m54s', '-63°01\'82\"'),
(22, 'Corbeau', 'Corvus', 'Crv', 183.801, 0.45, '12h26m52s', '-18°26\'20\"	'),
(23, 'Coupe', 'Crater', 'Crt', 282.398, 0.68, '11h23m75s', '-15°55\'74\"'),
(24, 'Couronne australe', 'Corona Australis', 'CrA', 127.696, 0.31, '18h38m79s', '-41°08\'85\"'),
(25, 'Couronne boréale', 'Corona Borealis', 'CrB', 178.71, 0.43, '15h50m59s', '+32°37\'49\"'),
(26, 'Croix du Sud', 'Crux', 'Cru', 68.447, 0.17, '12h26m99s', '-60°11\'19\"'),
(27, 'Cygne', 'Cygnus', 'Cyg', 803.983, 1.95, '20h35m28s', '+44°32\'70\"'),
(28, 'Dauphin', 'Delphinus', 'Del', 188.549, 0.46, '20h41m61s', '+11°40′26″'),
(29, 'Dorade', 'Dorado', 'Dor', 179.173, 0.43, '05h14m51s', '-59°23′22″'),
(30, 'Dragon', 'Draco', 'Dra', 1082.95, 2.63, '15h08m64s', '+67°00′40″'),
(31, 'Ecu de Sobieski', 'Scutum', 'Sct', 109.114, 0.26, '18h40m39s', '-09°53′32″'),
(32, 'Eridan', 'Eridanus', 'Eri', 1137.92, 2.76, '03h18m02s', '-28°45′37″'),
(33, 'Fléche', 'Sagitta', 'Sge', 79.932, 0.19, '19h39m05s', '+18°51′68″'),
(34, 'Fourneau', 'Fornax', 'For', 397.502, 0.96, '02h47m88s', '-31°38′07″'),
(35, 'Gémeaux', 'Gemini', 'Gem', 513.761, 1.25, '07h04m24s', '+22°36′01″'),
(36, 'Girafe', 'Camelopardalis', 'Cam', 756.828, 1.83, '08h51m37s', '+69°22′89″'),
(37, 'Grand Chien', 'Canis Major', 'CMa', 380.118, 0.92, '06h49m74s', '-22°08′42″'),
(38, 'Grande Ourse', 'Ursa Major', 'UMa', 1279.66, 3.1, '11h18m76s', '+50°43′27″'),
(39, 'Grue', 'Grus', 'Gru', 365.513, 0.89, '22h27m39s', '-46°21′11″'),
(40, 'Hercule', 'Hercules', 'Her', 1225.15, 2.97, '17h23m16s', '+27°29′93″'),
(41, 'Horloge', 'Horologium', 'Hor', 248.885, 0.6, '03h16m56s', '-53°20′18″'),
(42, 'Hydre', 'Hydra', 'Hya', 1302.84, 3.16, '11h36m73s', '-14°31′91″'),
(43, 'Hydre mâle', 'Hydrus', 'Hyi', 243.035, 0.59, '02h20m65s', '-69°57′39″'),
(44, 'Indien', 'Indus', 'Ind', 294.006, 0.71, '21h58m33s', '-59°42′40″'),
(45, 'Lézard', 'Lacerta', 'Lac', 200.688, 0.49, '22h27m68s', '+46°02′51″'),
(46, 'Licorne', 'Monoceros', 'Mon', 481.569, 1.17, '07h03m63s', '+00°16′93″'),
(47, 'Lièvre', 'Lepus', 'Lep', 290.291, 0.7, '05h33m95s', '-19°02′78″'),
(48, 'Lion', 'Leo', 'Leo', 946.964, 2.3, '10h40m03s', '+13°08′32″'),
(49, 'Loup', 'Lupus', 'Lup', 333.683, 0.81, '15h13m21s', '-42°42′53″'),
(50, 'Lynx', 'Lynx', 'Lyn', 545.386, 1.32, '07h59m53s', '+47°28′00″'),
(51, 'Lyre', 'Lyra', 'Lyr', 286.476, 0.69, '18h51m17s', '+36°41′36″'),
(52, 'La Machine pneumatique', 'Antlia', 'Ant', 238.901, 0.58, '10h16m43s', '-32°29′01″'),
(53, 'Microscope', 'Microscopium', 'Mic', 209.513, 0.51, '20h57m88s', '-36°16′49″'),
(54, 'Mouche', 'Musca', 'Mus', 138.355, 0.34, '12h35m28s', '-70°09′66″'),
(55, 'Octant', 'Octans', 'Oct', 291.045, 0.71, '23h00m00s', '-82°09′12″'),
(56, 'Oiseau de paradis', 'Apus', 'Aps', 206.327, 0.5, '16h08m65s', '-75°18′00″'),
(57, 'Ophiuchus', 'Ophiuchus', 'Oph', 948.34, 2.3, '17h23m69s', '-07°54′74″'),
(58, 'Orion', 'Orion', 'Ori', 594.12, 1.44, '05h34m59s', '+05°56′94″'),
(59, 'Paon', 'Pavo', 'Pav', 377.666, 0.92, '19h36m71s', '-65°46′89″'),
(60, 'Pégase', 'Pegasus', 'Peg', 1120.79, 2.72, '22h41m84s', '+19°27′98″'),
(61, 'Peintre', 'Pictor', 'Pic', 246.739, 0.6, '05h42m46s', '-53°28′45″'),
(62, 'Persée', 'Perseus', 'Per', 614.997, 1.49, '03h10m50s', '+45°00′79″'),
(63, 'Petit Cheval', 'Equuleus', 'Equ', 71.641, 0.17, '21h11m26s', '+07°45′49″'),
(64, 'Petit Chien', 'Canis Minor', 'CMi', 183.367, 0.44, '07h39m17s', '+06°25′63″'),
(65, 'Petit Lion', 'Leo Minor', 'LMi', 231.956, 0.56, '10h14m72s', '+32°08′08″'),
(66, 'Petit Renard', 'Vulpecula', 'Vul', 268.165, 0.65, '20h13m88s', '+24°26′56″'),
(67, 'Petite Ourse', 'Ursa Minor	', 'UMi', 255.864, 0.62, '15h00m00s', '+77°41′99″'),
(68, 'Phénix', 'Phoenix', 'Phe', 469.319, 1.14, '00h55m91s', '-48°34′84″'),
(69, 'Poisson austral', 'Piscis Austrinus', 'PsA', 245.375, 0.59, '22h17m07s', '-30°38′53″'),
(70, 'Le Poisson volant', 'Volans', 'Vol', 141.354, 0.34, '07h47m73s', '-69°48′07″'),
(71, 'Poissons', 'Pisces', 'Psc', 889.417, 2.16, '00h28m97s', '+13°41′23″'),
(72, 'Poupe', 'Puppis', 'Pup', 673.434, 1.63, '07h15m48s', '-31°10′64″'),
(73, 'Règle', 'Norma', 'Nor', 165.29, 0.4, '15h54m18s', '-51°21′09″'),
(74, 'Réticule', 'Reticulum', 'Ret', 113.936, 0.28, '03h55m27s', '-59°59′85″'),
(75, 'Sagittaire', 'Sagittarius', 'Sgr', 867.432, 2.1, '19h05m94s', '-28°28′61″'),
(76, 'Scorpion', 'Scorpius', 'Sco', 496.783, 1.2, '16h53m24s', '-27°01′89″'),
(77, 'Sculpteur', 'Sculptor', 'Scl', 474.764, 1.15, '00h26m28s', '-32°05′30″'),
(78, 'Serpent', 'Serpens', 'Ser', 636.928, 1.54, '16h57m04s', '+06°07′32″'),
(79, 'Sextant', 'Sextans', 'Sex', 313.515, 0.76, '10h16m29s', '-02°36′88″'),
(80, 'Table', 'Mensa', 'Men', 153.484, 0.37, '05h24m90s', '-77°30′24″'),
(81, 'Taureau', 'Taurus', 'Tau', 797.249, 1.93, '04h42m13s', '+14°52′63″'),
(82, 'Télescope', 'Telescopium', 'Tel', 251.512, 0.61, '23h46m64s', '-65°49′80″'),
(83, 'Toucan', 'Tucana', 'Tuc', 294.557, 0.71, '02h11m07s', '+31°28′56″'),
(84, 'Triangle', 'Triangulum', 'Tri', 131.847, 0.32, '16h04m95s', '+32°23′28″'),
(85, 'Triangle austral', 'Triangulum Australe', 'TrA', 109.978, 0.27, '19h19m54s', '-51°02′21″'),
(86, 'Verseau', 'Aquarius', 'Aqr', 979.854, 2.38, '22h17m38s', '-10°47′35″'),
(87, 'Vierge', 'Virgo', 'Vir', 1294.43, 3.14, '13h24m39s', '-04°09′51″'),
(88, 'Les Voiles', 'Vela', 'Vel', 499.649, 1.21, '09h34m64s', '-47°10\'03\"');

-- --------------------------------------------------------

--
-- Structure de la table `objects`
--

CREATE TABLE `objects` (
  `objects_id` int(6) UNSIGNED NOT NULL,
  `object_name` varchar(256) DEFAULT NULL,
  `object_messier` int(3) UNSIGNED DEFAULT NULL,
  `object_ngc` int(4) UNSIGNED DEFAULT NULL,
  `object_othername1` varchar(256) DEFAULT NULL,
  `object_othername2` varchar(256) DEFAULT NULL,
  `object_category` int(11) UNSIGNED DEFAULT NULL,
  `object_constellation` int(11) UNSIGNED DEFAULT NULL,
  `object_apparent_magnitude` float DEFAULT NULL,
  `object_secondary_magnitude` float DEFAULT NULL,
  `object_right_ascension` varchar(12) NOT NULL,
  `object_declination` varchar(12) NOT NULL,
  `object_appreciation` text DEFAULT NULL,
  `object_note` int(2) UNSIGNED DEFAULT NULL,
  `object_skymap1_id` int(10) UNSIGNED NOT NULL,
  `object_skymap2_id` int(11) UNSIGNED NOT NULL,
  `object_skymap3_id` int(11) UNSIGNED NOT NULL,
  `object_distance` double UNSIGNED DEFAULT NULL,
  `object_diameter` double UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `objects`
--

INSERT INTO `objects` (`objects_id`, `object_name`, `object_messier`, `object_ngc`, `object_othername1`, `object_othername2`, `object_category`, `object_constellation`, `object_apparent_magnitude`, `object_secondary_magnitude`, `object_right_ascension`, `object_declination`, `object_appreciation`, `object_note`, `object_skymap1_id`, `object_skymap2_id`, `object_skymap3_id`, `object_distance`, `object_diameter`) VALUES
(1, 'Nébuleuse de l\'haltère', 27, 6853, 'Dumbbell', 'Nébuleuse du trognon de pomme', 16, 66, 7.4, NULL, '19h59m36.34s', '22°43′16.1″', 'Large et plutôt lumineux,\r\npas mal à faire en public.', 8, 1, 1, 10, 1360, 2.88),
(2, 'Amas d\'Hercule', 13, 6205, NULL, NULL, 6, 40, 5.8, NULL, '6h41m41.44s', '36°27\'36.9\"', 'Très dense, lumineux et bien défini', 9, 1, 1, 10, 22180, 145),
(3, 'Nébuleuse d\'Orion', 42, 1976, NULL, NULL, 17, 58, 3.7, NULL, '05h35m16.5s', '-05°23′23\"', 'Coeur très lumineux et facile à trouver', 9, 1, 1, 14, 1344, 24);

-- --------------------------------------------------------

--
-- Structure de la table `skymap1`
--

CREATE TABLE `skymap1` (
  `skymap1_id` int(10) UNSIGNED NOT NULL,
  `skymap1_number` int(10) UNSIGNED NOT NULL,
  `skymap1_right_ascension` varchar(12) NOT NULL,
  `skymap1_declination` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Déchargement des données de la table `skymap1`
--

INSERT INTO `skymap1` (`skymap1_id`, `skymap1_number`, `skymap1_right_ascension`, `skymap1_declination`) VALUES
(1, 1, '0', '0');

-- --------------------------------------------------------

--
-- Structure de la table `skymap2`
--

CREATE TABLE `skymap2` (
  `skymap2_id` int(10) UNSIGNED NOT NULL,
  `skymap2_number` int(10) UNSIGNED NOT NULL,
  `skymap2_right_ascension` varchar(12) NOT NULL,
  `skymap2_declination` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Déchargement des données de la table `skymap2`
--

INSERT INTO `skymap2` (`skymap2_id`, `skymap2_number`, `skymap2_right_ascension`, `skymap2_declination`) VALUES
(1, 1, '0', '0');

-- --------------------------------------------------------

--
-- Structure de la table `skymap3`
--

CREATE TABLE `skymap3` (
  `skymap3_id` int(10) UNSIGNED NOT NULL,
  `skymap3_number` int(10) UNSIGNED NOT NULL,
  `skymap3_right_ascension` varchar(12) NOT NULL,
  `skymap3_declination` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Déchargement des données de la table `skymap3`
--

INSERT INTO `skymap3` (`skymap3_id`, `skymap3_number`, `skymap3_right_ascension`, `skymap3_declination`) VALUES
(1, 1, '00h00m00s', '+72°30\'00\"'),
(2, 2, '06h00m00s', '+72°30\'00\"'),
(3, 3, '12h00m00s', '+72°30\'00\"'),
(4, 4, '18h00m00s', '+72°30\'00\"'),
(5, 5, '01h42m51s', '+36°15\'00\"'),
(6, 6, '05h08m34s', '+36°15\'00\"'),
(7, 7, '08h34m17s', '+36°15\'00\"'),
(8, 8, '12h00m00s', '+36°15\'00\"'),
(9, 9, '15h25m43s', '+36°15\'00\"'),
(10, 10, '18h51m26s', '+36°15\'00\"'),
(11, 11, '22h17m09s', '+36°15\'00\"'),
(12, 12, '00h00m00s', '+00°00\'00\"'),
(13, 13, '03h00m00s', '+00°00\'00\"'),
(14, 14, '06h00m00s', '+00°00\'00\"'),
(15, 15, '09h00m00s', '+00°00\'00\"'),
(16, 16, '12h00m00s', '+00°00\'00\"'),
(17, 17, '15h00m00s', '+00°00\'00\"'),
(18, 18, '18h00m00s', '+00°00\'00\"'),
(19, 19, '21h00m00s', '+00°00\'00\"'),
(20, 20, '01h42m51s', '-36°15\'00\"'),
(21, 21, '5h8m34s', '-36°15\'00\"'),
(22, 22, '8h34m17s', '-36°15\'00\"'),
(23, 23, '12h00m00s', '-36°15\'00\"'),
(24, 24, '15h00m00s', '-36°15\'00\"'),
(25, 25, '18h51m26s', '-36°15\'00\"'),
(26, 26, '22h17m09s', '-36°15\'00\"'),
(27, 27, '00h00m00s', '-72°30\'00\"'),
(28, 28, '06h00m00s', '-72°30\'00\"'),
(29, 29, '12h00m00s', '-72°30\'00\"'),
(30, 30, '18h00m00s', '-72°30\'00\"');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`category_id`);

--
-- Index pour la table `constellations`
--
ALTER TABLE `constellations`
  ADD PRIMARY KEY (`constellation_id`);

--
-- Index pour la table `objects`
--
ALTER TABLE `objects`
  ADD PRIMARY KEY (`objects_id`),
  ADD KEY `object_constellation` (`object_constellation`),
  ADD KEY `object_category` (`object_category`),
  ADD KEY `object_skymap3_id` (`object_skymap3_id`),
  ADD KEY `object_skymap2_id` (`object_skymap2_id`),
  ADD KEY `object_skymap1_id` (`object_skymap1_id`);

--
-- Index pour la table `skymap1`
--
ALTER TABLE `skymap1`
  ADD PRIMARY KEY (`skymap1_id`);

--
-- Index pour la table `skymap2`
--
ALTER TABLE `skymap2`
  ADD PRIMARY KEY (`skymap2_id`);

--
-- Index pour la table `skymap3`
--
ALTER TABLE `skymap3`
  ADD PRIMARY KEY (`skymap3_id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `categories`
--
ALTER TABLE `categories`
  MODIFY `category_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT pour la table `constellations`
--
ALTER TABLE `constellations`
  MODIFY `constellation_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=89;

--
-- AUTO_INCREMENT pour la table `objects`
--
ALTER TABLE `objects`
  MODIFY `objects_id` int(6) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT pour la table `skymap1`
--
ALTER TABLE `skymap1`
  MODIFY `skymap1_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT pour la table `skymap2`
--
ALTER TABLE `skymap2`
  MODIFY `skymap2_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT pour la table `skymap3`
--
ALTER TABLE `skymap3`
  MODIFY `skymap3_id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `objects`
--
ALTER TABLE `objects`
  ADD CONSTRAINT `objects_ibfk_1` FOREIGN KEY (`object_category`) REFERENCES `categories` (`category_id`),
  ADD CONSTRAINT `objects_ibfk_2` FOREIGN KEY (`object_constellation`) REFERENCES `constellations` (`constellation_id`),
  ADD CONSTRAINT `objects_ibfk_3` FOREIGN KEY (`object_skymap1_id`) REFERENCES `skymap1` (`skymap1_id`),
  ADD CONSTRAINT `objects_ibfk_4` FOREIGN KEY (`object_skymap2_id`) REFERENCES `skymap2` (`skymap2_id`),
  ADD CONSTRAINT `objects_ibfk_5` FOREIGN KEY (`object_skymap3_id`) REFERENCES `skymap3` (`skymap3_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
